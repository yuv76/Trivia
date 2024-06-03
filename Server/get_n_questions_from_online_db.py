import requests
import sqlite3
import json
import sys #for cmd arguments

def main():
    args = sys.argv[1:]
    num = 0
    if len(args) > 0:
        num = int(args[0])
    else:
        num = 1
    
    # Perform a GET request to a URL
    response = requests.get('https://opentdb.com/api.php?amount=' + str(num) + '&type=multiple')
    
    conn = sqlite3.connect('SqliteDatabase.db')
    
    json_object = json.loads(response.content.decode())
    individual_json_strings = json_object['results']
    
    cur = conn.cursor()
    
    for i in individual_json_strings:
    
        wrongs = i["incorrect_answers"]
        
        sql_command = "INSERT INTO questions('right answer', '1 wrong answer', '2 wrong answer', '3 wrong answer', 'question', 'difficulty') VALUES('" + i["correct_answer"] + "', '" + wrongs[0] + "', '" + wrongs[1] + "', '" + wrongs[2] + "', '" + i["question"] + "', '" + i["difficulty"] +"')"
        cur.execute(sql_command)
        
        conn.commit()
        
    conn.close()
        
    
if __name__ == "__main__":
    main()