import json

import xmltodict
from django.http import HttpResponse
from django.shortcuts import render
from json_flatten import flatten


def xml2json(string: bytes):
    json_data = xmltodict.parse(string)
    json_string = json.dumps(json_data)
    return json_string.encode("utf-8")


def json2xml(data):
    xml_data = xmltodict.unparse(json.loads(data))
    return xml_data


def json2html(byte_data: bytes) -> HttpResponse:
    json_data = json.loads(byte_data.decode())
    flat_data = flatten(json_data)
    first_key = next(iter(flat_data))

    if first_key != "data":
        flat_data = {'data': flat_data}

    rendered_html = render(None, '../templates/html/default.html', flat_data)
    return rendered_html


def csv2json(response):
    csv_data = response.text
    rows = []
    lines = csv_data.splitlines()
    header = lines[0].split(',')
    for line in lines[1:]:
        values = line.split(',')
        row_dict = {header[i]: values[i] for i in range(len(header))}
        rows.append(row_dict)

    data = json.dumps(rows)
    return data
