"""Normalize a saved Marvel JSON snapshot into two validated CSV files."""
import argparse
import csv
import json
from pathlib import Path

KINDS = {0: "friend", 1: "enemy", 2: "creation", 3: "family", 4: "work", 5: "love"}


def records(value):
    if isinstance(value, dict):
        return value.values()
    if isinstance(value, list):
        return value
    raise ValueError("Expected a collection of records")


def required_text(value, field):
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"Missing or invalid {field}: {value!r}")
    return value.strip()


def normalize(snapshot):
    characters = {}
    for row in records(snapshot["characters"]):
        identity = required_text(row["id"], "character id")
        if identity in characters:
            raise ValueError(f"Duplicate character id: {identity}")
        characters[identity] = {
            "id": identity,
            "name": required_text(row["name"], "character name"),
            "status": row.get("status") or "",
            "species": row.get("species") or "",
        }

    relationships = set()
    for row in records(snapshot["relationship"]):
        source = required_text(row["id"], "relationship source")
        target = required_text(row["target_id"], "relationship target")
        if source not in characters or target not in characters:
            raise ValueError(f"Unknown endpoint: {source} -> {target}")
        code = str(row["relationship"])
        if code not in {str(key) for key in KINDS}:
            raise ValueError(f"Unsupported relationship kind: {code}")
        kind = KINDS[int(code)]
        relationships.add((source, target, kind))

    nodes = [characters[key] for key in sorted(characters)]
    edges = [dict(zip(("source_id", "target_id", "kind"), edge))
             for edge in sorted(relationships)]
    return nodes, edges


def write_csv(path, fields, rows):
    with path.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("snapshot", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    snapshot = json.loads(args.snapshot.read_text(encoding="utf-8"))
    nodes, edges = normalize(snapshot)  # Validate before writing either file.
    args.output.mkdir(parents=True, exist_ok=True)
    write_csv(args.output / "characters.csv", ["id", "name", "status", "species"], nodes)
    write_csv(args.output / "relationships.csv", ["source_id", "target_id", "kind"], edges)
    print(f"Prepared {len(nodes)} characters and {len(edges)} directed relationships")


if __name__ == "__main__":
    main()
