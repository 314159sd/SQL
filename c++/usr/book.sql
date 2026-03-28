CREATE TABLE `books` (
  `bookid` int NOT NULL AUTO_INCREMENT COMMENT '图书ID，自增主键',
  `title` varchar(200) NOT NULL COMMENT '图书名称',
  `author` varchar(100) DEFAULT NULL COMMENT '作者',
  `isbn` varchar(13) DEFAULT NULL COMMENT 'ISBN编号，唯一约束',
  `publisher` varchar(100) DEFAULT NULL COMMENT '出版社',
  `publishyear` year DEFAULT NULL COMMENT '出版年份',
  `category` varchar(50) DEFAULT NULL COMMENT '图书分类',
  `totalcopies` int DEFAULT '1' COMMENT '总库存',
  `availablecopies` int DEFAULT '1' COMMENT '可借数量',
  `createdate` timestamp NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建日期',
  PRIMARY KEY (`bookid`),
  UNIQUE KEY `isbn` (`isbn`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci