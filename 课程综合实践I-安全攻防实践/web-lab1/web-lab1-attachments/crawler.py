import json
from requests import Session

def process_grade_data(raw_data, semester_prefix):
    try:
        parsed_data = json.loads(raw_data)
    except json.JSONDecodeError:
        print(f"Error parsing JSON data: {raw_data}")
        return []
    processed_grades = []
    for entry in parsed_data.get("items", []):
        course_code = entry.get("xkkh", "")
        if semester_prefix and not course_code.startswith(semester_prefix):
            continue
        grade_entry = {
            "课程": entry.get("kcmc"),
            "学分": entry.get("xf"),
            "绩点": entry.get("jd"),
            "得分": entry.get("cj")
        }
        processed_grades.append(grade_entry)

    return processed_grades

def retrieve_academic_records(api_endpoint, auth_cookies, semester_prefix=""):
    http_client = Session()
    http_client.cookies.update(auth_cookies)

    complete_records = []
    semester_records = []
    current_page = 1
    entries_per_page = 20

    while True:
        query_params = {
            "doType": "query",
            "queryModel.showCount": entries_per_page,
            "queryModel.currentPage": current_page,
            "queryModel.sortName": "xkkh",
            "queryModel.sortOrder": "asc",
            "time": 1,
        }
        response = http_client.post(api_endpoint, data=query_params)
        if response.status_code != 200:
            print(f"API request failed with status code: {response.status_code}")
            break
        response_content = response.content.decode()

        semester_data = process_grade_data(response_content, semester_prefix)
        semester_records.extend(semester_data)
        complete_records.extend(process_grade_data(response_content, ""))

        if len(semester_data) < entries_per_page:
            break

        current_page += 1

    return complete_records, semester_records

student_id = "" 
base_url = "http://zdbk.zju.edu.cn/jwglxt/cxdy/xscjcx_cxXscjIndex.html"
api_endpoint = f"{base_url}?&gnmkdm=N508301&su={student_id}"
auth_cookies = {}  
semester_prefix = ""  

full_academic_history, current_semester_grades = retrieve_academic_records(api_endpoint, auth_cookies, semester_prefix)
print(f"\nComplete Academic History:\n{full_academic_history}\n\nCurrent Semester Grades:\n{current_semester_grades}")