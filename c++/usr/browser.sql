CREATE TABLE borrows ( 
 borrowid INT AUTO_INCREMENT PRIMARY KEY COMMENT '借阅记录ID，自增主键',
 bookid INT COMMENT '关联图书ID', 
 readerid INT COMMENT '关联读者ID',
 borrowdate timestamp DEFAULT NOW() COMMENT '借阅时间', 
 duedate DATE NOT NULL COMMENT '应还日期', 
 returndate TIMESTAMP NULL COMMENT '实际归还时间', 
 status ENUM('borrowed', 'returned', 'overdue') DEFAULT 'borrowed' COMMENT '借阅状态', 
 -- 外键约束，确保记录关联有效 
 FOREIGN KEY (bookid) REFERENCES books(bookid) ON DELETE CASCADE, 
 FOREIGN KEY (readerid) REFERENCES readers(readerid) ON DELETE CASCADE );