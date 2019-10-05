from flask import Flask, render_template, request, redirect, url_for
import pymysql

app = Flask(__name__)

# creating connection Object which will contain SQL Server Connection
host = "localhost"
port = 3306
dbname = "attendance"
user = "root"
password = "Anthony10c1997"

conn = pymysql.connect(host, user=user, port=port,
                       password=password, db=dbname)
# connection = pypyodbc.connect('Driver={SQL Server};Server=.\FASCELSQLSERVER;Database=demo;uid=sa;pwd=Fascelsql')# Creating C
cursor = conn.cursor()

     
@app.route('/')
def home():        
    return redirect(url_for('login'))
  

@app.route('/first', methods=['GET', 'POST'])
def first():
    if request.method == 'POST':
        if request.form.get('VLSI') == 'VLSI':
            cursor.execute(
                "SELECT s.SID,s.SRoll,s.SName,COUNT(*) Lectures_Attended FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, '%') WHERE e.TID = (select TID from teacher where TSubject='VLSI') GROUP BY s.SID")
            data = cursor.fetchall()
            return render_template('studentslist.html', data=data)

        elif request.form.get('Embedded Systems Attendance') == 'Embedded Systems Attendance':
            cursor.execute(
                "SELECT s.SID,s.SRoll,s.SName,COUNT(*) Lectures_Attended FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, '%') WHERE e.TID = (select TID from teacher where TSubject='Embedded Systems') GROUP BY s.SID")
            data = cursor.fetchall()
            return render_template('studentslist.html', data=data)        
       
        elif request.form.get('Digital Processing') == 'Digital Processing':
            cursor.execute(
                "SELECT s.SID,s.SRoll,s.SName,COUNT(*) Lectures_Attended FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, '%') WHERE e.TID = (select TID from teacher where TSubject='Digital Processing') GROUP BY s.SID")
            data = cursor.fetchall()
            return render_template('studentslist.html', data=data)

        elif request.form.get('Lectures Conducted') == 'Lectures Conducted':
            cursor.execute(
                "SELECT t.TSubject,t.TName,t.TID, COUNT(*) Lectures_Conducted FROM teacher t INNER JOIN status_attendance s ON s.TID LIKE CONCAT(t.TID, '%') group by s.TID")
            data = cursor.fetchall()
            return render_template('studentslist2.html', data=data)

        elif request.form.get('Total Attendance') == 'Total Attendance':
            cursor.execute(
                "SELECT s.SID,s.SRoll,s.SName, COUNT(*) as Total_Lectures_Attended FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, '%')   GROUP BY s.SID")
            data = cursor.fetchall()
            return render_template('studentslist.html', data=data)                                 
                     
    elif request.method == 'GET':                                                     
     return render_template('first.jsp')  
         

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':   
        cursor.execute("SELECT * FROM admin1 ")
        for row in cursor:
            email = row[0]
            print(email)
            password1 = row[1]
            print(password1)
            if request.form['email'] == email and request.form['password'] == password1:
                return redirect(url_for('first'))
    else:
        error = 'Invalid Credentials. Please try again.'

    return render_template('index.html', error=error)  
    # if request.method == 'POST':
    # if request.form['email'] != 'merly@fragnel.in' or request.form['password'] != 'msmerly':
    # error = 'Invalid Credentials. Please try again.'
    # else:
    # return redirect(url_for('first'))return render_template('login.html',error=error)


if __name__ == '__main__':
    app.run(debug=True, use_reloader=True)

