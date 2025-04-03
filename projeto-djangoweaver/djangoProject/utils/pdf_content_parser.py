from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.platypus import Paragraph, Table
from reportlab.platypus.tables import TableStyle


def build_auto_pdf_from_content(story: list, mapping_content: dict) -> list:
    """under the assumption that any list of content follows the type structure:
    string, bool, number, null, object, array
    a story will be built with no regard to order,
    to output every piece of information in PDF format"""
    styles = getSampleStyleSheet()
    style_custom = styles["BodyText"]
    style_custom.wordWrap = 'LTR'  # 'LTR' for left-to-right text wrapping

    for key, value in mapping_content.items():
        if isinstance(value, str):
            print(f"The item '{value}' is a string.")
            story.append(Paragraph(value, style_custom))
        elif isinstance(value, bool):
            print(f"The value '{value}' is a boolean.")
            story.append(Paragraph(str(value), style_custom))
        elif isinstance(value, int):
            print(f"The value '{value}' is an integer.")
            story.append(Paragraph(str(value), style_custom))
        elif isinstance(value, float):
            print(f"The value '{value}' is a float.")
            story.append(Paragraph(str(value), style_custom))
        elif value is None:
            print(f"The value '{value}' is None (null).")
            pass
        elif isinstance(value, dict):
            print(f"The value '{value}' is a dictionary.")
            # story.append(Paragraph(str(key), style_custom)) ''' Hiding labels of object'''
            story = build_auto_pdf_from_content(story, value)
        elif isinstance(value, list):
            print(f"The item '{value}' is a list.")
            # value = [['Notas'], [1, 2, 3]]

            if all(isinstance(i, dict) for i in value):
                # story.append(Paragraph(str(key), style_custom)) ''' Hiding labels of object'''
                for item in value:
                    story = build_auto_pdf_from_content(story, item)
            else:
                # story.append(Paragraph(str(key), style_custom)) ''' Hiding labels of object'''
                value = check_and_convert(value)
                cells = []

                for element in value:
                    line = []
                    for item in element:
                        paragraph = Paragraph(str(item), style_custom)
                        line.append(paragraph)
                    cells.append(line)

                table = Table(cells)
                #table.wrapOn(None, 0, 0)

                table.setStyle(TableStyle([
                    ('BACKGROUND', (0, 0), (-1, 0), colors.grey),
                    ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
                    ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
                    ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
                    ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
                    ('BACKGROUND', (0, 1), (-1, -1), colors.beige),
                    ('GRID', (0, 0), (-1, -1), 1, colors.black),
                    ('VALIGN', (0, 0), (-1, -1), 'TOP'),  # Ensure vertical alignment is set to top
                    ('LEFTPADDING', (0, 0), (-1, -1), 5),  # Add padding to avoid text touching cell borders
                    ('RIGHTPADDING', (0, 0), (-1, -1), 5),
                    ('TOPPADDING', (0, 0), (-1, -1), 5),
                    ('BOTTOMPADDING', (0, 0), (-1, -1), 5),
                ]))

                story.append(table)
        else:
            print(f"The item '{value}' is of an unknown type.")
            pass
    return story


def is_list_of_lists(lst):
    return all(isinstance(i, list) for i in lst)


def make_two_dimensional(lst):
    # empty list here works as a placeholder label list
    return [lst]


def check_and_convert(lst):
    # checks if lst is a list of lists
    if is_list_of_lists(lst):
        pass
    else:
        # print("The list is a one-dimensional list. Converting to a two-dimensional list.")
        lst = make_two_dimensional(lst)
    return lst


