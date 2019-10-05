SELECT * FROM attendance.status_attendance;
SELECT t.TSubject,t.TName,t.TID, COUNT(*) Lectures_Conducted FROM teacher t 
INNER JOIN status_attendance s ON s.TID LIKE CONCAT(t.TID, "%")  
WHERE s.TID = (select TID from teacher where TSubject="VLSI") GROUP BY t.TID