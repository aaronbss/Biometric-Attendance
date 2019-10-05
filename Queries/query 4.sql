SELECT s.SID,s.SRoll,s.SName, COUNT(*) as Total_Lectures_Attended FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, "%")   GROUP BY s.SID

