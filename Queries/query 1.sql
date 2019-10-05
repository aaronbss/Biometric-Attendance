SELECT * FROM attendance.elex_attendance;
delete from elex_attendance Where TID="99";
SET SQL_SAFE_UPDATES = 0;
SELECT s.SID, COUNT(*) num FROM student s INNER JOIN elex_attendance e ON e.SID LIKE CONCAT(s.SID, "%")  WHERE e.TID = (select TID from teacher where TSubject="VLSI") GROUP BY s.SID
Select s.SName, Count(*) from student s join elex_attendance e on s.SID=e.SID where e.TID=(select TID from teacher where TSubject="VLSI");
ALTER TABLE elex_attendance DROP stamp;