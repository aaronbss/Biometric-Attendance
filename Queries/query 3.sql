SELECT s.SID,s.SRoll,s.SName, COUNT(*) Lectures_Attended FROM student s 
INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, "%")  
WHERE e.TID = (select TID from teacher where TSubject="Embedded Systems") GROUP BY s.SID
