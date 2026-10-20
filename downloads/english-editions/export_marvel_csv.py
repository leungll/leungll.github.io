"""Fetch or read Marvel JSON and export the three CSV files used by Neo4j."""
import argparse
import csv
import json
from pathlib import Path
from urllib.request import Request, urlopen

KINDS = {0: "friend", 1: "enemy", 2: "creation", 3: "family", 4: "work", 5: "love"}


def records(value):
    if isinstance(value, dict):
        return value.values()
    if isinstance(value, list):
        return value
    raise ValueError("Expected a record collection")


def character_key(value):
    if not isinstance(value, str) or not value.strip():
        raise ValueError("A character key must be a nonempty string")
    return value.strip()


def prepare_rows(data):
    characters = {}
    for item in records(data["characters"]):
        key = character_key(item["id"])
        if key in characters:
            raise ValueError(f"Duplicate character key: {key}")
        characters[key] = item

    relationships, used = [], set()
    for item in records(data["relationship"]):
        source = character_key(item["id"])
        target = character_key(item["target_id"])
        if source not in characters or target not in characters:
            raise ValueError(f"Unknown endpoint: {source} -> {target}")
        raw_kind = str(item["relationship"])
        if raw_kind not in {str(key) for key in KINDS}:
            raise ValueError(f"Unsupported relationship code: {raw_kind}")
        relationships.append((source, target, KINDS[int(raw_kind)]))
        used.update((source, target))

    names = [(key, index) for index, key in enumerate(sorted(used), start=1)]
    messages = [
        (key, item.get("name") or "", item.get("status") or "", item.get("species") or "")
        for key, item in sorted(characters.items())
    ]
    return names, relationships, messages


def write_csv(path, header, rows):
    with path.open("w", encoding="utf-8", newline="") as stream:
        writer = csv.writer(stream)
        writer.writerow(header)
        writer.writerows(rows)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument("--url")
    source.add_argument("--input", type=Path)
    parser.add_argument("--output", type=Path, default=Path("prepared"))
    args = parser.parse_args()
    if args.url:
        request = Request(args.url, headers={"User-Agent": "MarvelGraphTutorial/1.0"})
        with urlopen(request, timeout=30) as response:
            raw = response.read().decode("utf-8-sig")
    else:
        raw = args.input.read_text(encoding="utf-8-sig")
    names, relations, messages = prepare_rows(json.loads(raw))
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "marvel-data.json").write_text(raw, encoding="utf-8")
    write_csv(args.output / "names_message.csv", ["name", "id"], names)
    write_csv(args.output / "relation_message.csv", ["subject", "object", "relation"], relations)
    write_csv(args.output / "message.csv", ["id", "name", "status", "species"], messages)
    print(f"Exported {len(names)} referenced characters and {len(relations)} relationships")


if __name__ == "__main__":
    main()
