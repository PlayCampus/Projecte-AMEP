-- MySQL dump 10.13  Distrib 8.0.38, for Win64 (x86_64)
--
-- Host: ubiwan.epsevg.upc.edu    Database: amep06
-- ------------------------------------------------------
-- Server version	5.5.5-10.11.14-MariaDB-0ubuntu0.24.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Administrador`
--

DROP TABLE IF EXISTS `Administrador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Administrador` (
  `identificador` int(11) NOT NULL,
  `telefonContacte` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`identificador`),
  CONSTRAINT `Administrador_ibfk_1` FOREIGN KEY (`identificador`) REFERENCES `Usuari` (`identificador`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Administrador`
--

LOCK TABLES `Administrador` WRITE;
/*!40000 ALTER TABLE `Administrador` DISABLE KEYS */;
INSERT INTO `Administrador` VALUES (2,'604403921'),(4,'63298476'),(6,'604507801'),(9,'604504720'),(17,'43242342'),(22,'634993924');
/*!40000 ALTER TABLE `Administrador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Capita`
--

DROP TABLE IF EXISTS `Capita`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Capita` (
  `identificador` int(11) NOT NULL,
  `telefonContacte` varchar(20) DEFAULT NULL,
  `idEquip` varchar(50) DEFAULT NULL,
  `validatPerAdmin` tinyint(1) DEFAULT 0,
  PRIMARY KEY (`identificador`),
  CONSTRAINT `Capita_ibfk_1` FOREIGN KEY (`identificador`) REFERENCES `Usuari` (`identificador`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Capita`
--

LOCK TABLES `Capita` WRITE;
/*!40000 ALTER TABLE `Capita` DISABLE KEYS */;
INSERT INTO `Capita` VALUES (3,'601204851','E-c6eb23ac',0),(5,'123456789','E-a3ee606a',0),(7,'123456789','E-f9d5abc7',0),(8,'601204501','E-d1fdbcbc',0),(11,'1234','E-8f9319cf',0),(13,'123456789','E-f453f197',0),(15,'1219839','E-8f221af6',0),(18,'390482','E-6d3e8892',0),(19,'604604704','E-52bfb5de',0),(20,'6767676767','E-440225a8',0),(21,'634993924','E-1ad8a8d7',0),(23,'112','E-4c09cb9d',0),(24,'634993924','E-2347b4e1',0);
/*!40000 ALTER TABLE `Capita` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Equip`
--

DROP TABLE IF EXISTS `Equip`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Equip` (
  `idEquip` varchar(100) NOT NULL,
  `nom` varchar(100) NOT NULL,
  `dataFundacio` datetime NOT NULL,
  `esport` varchar(100) NOT NULL,
  `partitsJugats` int(11) DEFAULT 0,
  `victories` int(11) DEFAULT 0,
  `derrotes` int(11) DEFAULT 0,
  `empats` int(11) DEFAULT 0,
  `punts` int(11) DEFAULT 0,
  `golsAFavor` int(11) DEFAULT 0,
  `golsEnContra` int(11) DEFAULT 0,
  `diferenciaGols` int(11) DEFAULT 0,
  `posicioClassificacio` int(11) DEFAULT 0,
  `idLliga` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`idEquip`),
  KEY `FK_Equip_Lliga` (`idLliga`),
  CONSTRAINT `FK_Equip_Lliga` FOREIGN KEY (`idLliga`) REFERENCES `Lliga` (`idLliga`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Equip`
--

LOCK TABLES `Equip` WRITE;
/*!40000 ALTER TABLE `Equip` DISABLE KEYS */;
INSERT INTO `Equip` VALUES ('E-1ad8a8d7','ProvaEquip','2026-04-05 12:58:20','Futbol',0,0,0,0,0,0,0,0,0,'L-5e2574d5'),('E-2347b4e1','Equip2','2026-04-08 13:30:25','Futbol',0,0,0,0,0,0,0,0,0,'L-5e2574d5'),('E-440225a8','nn','2026-04-08 09:54:05','Futbol',0,0,0,0,0,0,0,0,0,'L-a620be60'),('E-4c09cb9d','VilanovaFc','2026-04-08 11:40:52','Futbol',0,0,0,0,0,0,0,0,0,'L-a620be60'),('E-8f221af6','d.F.C','2026-04-02 15:59:39','Futbol',0,0,0,0,0,0,0,0,0,NULL),('E-8f9319cf','JoseFC','2026-04-01 18:43:26','Futbol',0,0,0,0,0,0,0,0,0,NULL),('E-9d0b0f3b','JordiFC','2001-07-05 22:09:20','Futbol',0,0,0,0,0,0,0,0,0,NULL),('E-9dc00dc4','JordiFC','2026-04-01 18:21:42','Futbol',0,0,0,0,0,0,0,0,0,'L-b329a883'),('E-a3ee606a','NOU','2026-04-01 01:34:11','Futbol',0,0,0,0,0,0,0,0,0,'L-be36f0c6'),('E-d1fdbcbc','Barça','1899-11-29 17:21:19','Futbol',0,0,0,0,0,0,0,0,0,'L-a620be60'),('E-f453f197','mec','2026-04-02 14:11:57','Voley',0,0,0,0,0,0,0,0,0,NULL),('E-f9d5abc7','PatataFC','2026-01-05 18:51:54','Futbol',0,0,0,0,0,0,0,0,0,'L-b329a883');
/*!40000 ALTER TABLE `Equip` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Estudiant`
--

DROP TABLE IF EXISTS `Estudiant`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Estudiant` (
  `identificador` int(11) NOT NULL,
  `carrera` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`identificador`),
  CONSTRAINT `Estudiant_ibfk_1` FOREIGN KEY (`identificador`) REFERENCES `Usuari` (`identificador`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Estudiant`
--

LOCK TABLES `Estudiant` WRITE;
/*!40000 ALTER TABLE `Estudiant` DISABLE KEYS */;
INSERT INTO `Estudiant` VALUES (1,''),(12,'');
/*!40000 ALTER TABLE `Estudiant` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Jornada`
--

DROP TABLE IF EXISTS `Jornada`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Jornada` (
  `idJornada` varchar(36) NOT NULL,
  `idTemporada` varchar(36) NOT NULL,
  `numero` int(11) NOT NULL,
  `dataInici` datetime NOT NULL,
  `dataFi` datetime NOT NULL,
  `estat` varchar(50) NOT NULL,
  PRIMARY KEY (`idJornada`),
  KEY `fk_jornada_temporada` (`idTemporada`),
  CONSTRAINT `fk_jornada_temporada` FOREIGN KEY (`idTemporada`) REFERENCES `Temporada` (`idTemporada`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Jornada`
--

LOCK TABLES `Jornada` WRITE;
/*!40000 ALTER TABLE `Jornada` DISABLE KEYS */;
INSERT INTO `Jornada` VALUES ('J-46dc5b8e','T-d1e40e03',1,'2026-04-08 12:23:36','2026-04-15 12:23:36','Proxim'),('J-ae36261d','T-1a1bd5fc',1,'2026-04-07 21:24:15','2026-04-14 21:24:15','Proxim'),('J-b24016b9','T-1a1bd5fc',2,'2026-04-15 11:47:38','2026-04-22 11:47:38','Proxim'),('J-e7f427f5','T-8a4536ec',1,'2026-04-08 13:26:10','2026-04-15 13:26:10','Proxim'),('J-f84939c1','T-03949b97',1,'2026-04-08 12:25:24','2026-04-15 12:25:24','Proxim');
/*!40000 ALTER TABLE `Jornada` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Lliga`
--

DROP TABLE IF EXISTS `Lliga`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Lliga` (
  `idLliga` varchar(36) NOT NULL,
  `nom` varchar(100) NOT NULL,
  `disciplina` varchar(50) NOT NULL,
  `descripcio` text DEFAULT NULL,
  `estat` varchar(50) NOT NULL,
  `contrasenya` varchar(255) DEFAULT NULL,
  `idAdministrador` int(11) DEFAULT NULL,
  PRIMARY KEY (`idLliga`),
  KEY `idAdministrador` (`idAdministrador`),
  CONSTRAINT `Lliga_ibfk_1` FOREIGN KEY (`idAdministrador`) REFERENCES `Administrador` (`identificador`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Lliga`
--

LOCK TABLES `Lliga` WRITE;
/*!40000 ALTER TABLE `Lliga` DISABLE KEYS */;
INSERT INTO `Lliga` VALUES ('L-34278f1c','ABC2','Basquet','Nova Lliga ABC2','en_curs','1234',17),('L-5e2574d5','LligaUniversitaria','Futbol','Nova Lliga LligaUniversitaria','en_curs','1234',22),('L-a620be60','M','Futbol','Nova Lliga M','en_curs','1234',6),('L-b329a883','La lliga','Futbol','Nova Lliga La lliga','en_curs','1234',9),('L-be36f0c6','ABC','Basquet','Nova Lliga ABC','en_curs','1234',2),('L-ca8c9c57','ENDESA','Basquet','Nova Lliga ENDESA','en_curs','1234',4);
/*!40000 ALTER TABLE `Lliga` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Partit`
--

DROP TABLE IF EXISTS `Partit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Partit` (
  `idPartit` varchar(36) NOT NULL,
  `idJornada` varchar(36) NOT NULL,
  `idEquipLocal` varchar(100) NOT NULL,
  `idEquipVisitant` varchar(100) NOT NULL,
  `dataHora` datetime NOT NULL,
  `ubicacio` varchar(255) DEFAULT NULL,
  `estat` varchar(50) DEFAULT 'Pendent',
  `golsLocal` int(11) DEFAULT NULL,
  `golsVisitant` int(11) DEFAULT NULL,
  PRIMARY KEY (`idPartit`),
  KEY `fk_partit_equip_local` (`idEquipLocal`),
  KEY `fk_partit_equip_visitant` (`idEquipVisitant`),
  CONSTRAINT `fk_partit_equip_local` FOREIGN KEY (`idEquipLocal`) REFERENCES `Equip` (`idEquip`) ON DELETE CASCADE,
  CONSTRAINT `fk_partit_equip_visitant` FOREIGN KEY (`idEquipVisitant`) REFERENCES `Equip` (`idEquip`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Partit`
--

LOCK TABLES `Partit` WRITE;
/*!40000 ALTER TABLE `Partit` DISABLE KEYS */;
INSERT INTO `Partit` VALUES ('11a1a5b8-64a0-4fba-a043-ebafcd45cab7','J-ae36261d','E-4c09cb9d','E-d1fdbcbc','2026-04-08 11:46:57','vijla','Pendent',0,0),('29794528-fac5-4ac3-9838-d0ff5f96e46c','J-ae36261d','E-440225a8','E-d1fdbcbc','2026-04-08 10:07:08','upc','Pendent',0,0),('734426b8-b880-4687-aecc-2dc543da9409','J-46dc5b8e','E-440225a8','E-4c09cb9d','2026-04-08 12:25:32','asdf','Pendent',0,0),('a19633e7-901c-4082-bf23-e609b2d4505f','J-46dc5b8e','E-1ad8a8d7','E-2347b4e1','2026-04-08 13:31:32','epsevg','Pendent',0,0);
/*!40000 ALTER TABLE `Partit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Temporada`
--

DROP TABLE IF EXISTS `Temporada`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Temporada` (
  `idTemporada` varchar(36) NOT NULL,
  `idLliga` varchar(36) NOT NULL,
  `dataInici` datetime NOT NULL,
  `dataFi` datetime NOT NULL,
  `estat` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idTemporada`),
  KEY `fk_temporada_lliga` (`idLliga`),
  CONSTRAINT `fk_temporada_lliga` FOREIGN KEY (`idLliga`) REFERENCES `Lliga` (`idLliga`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Temporada`
--

LOCK TABLES `Temporada` WRITE;
/*!40000 ALTER TABLE `Temporada` DISABLE KEYS */;
INSERT INTO `Temporada` VALUES ('T-03949b97','L-a620be60','2026-04-06 00:00:00','2026-10-06 00:00:00','Proxim'),('T-1a1bd5fc','L-a620be60','2026-04-06 00:00:00','2026-10-06 00:00:00','Proxim'),('T-3aa28f9b','L-a620be60','2028-04-08 00:00:00','2029-10-08 00:00:00','Proxim'),('T-8a4536ec','L-5e2574d5','2026-04-08 00:00:00','2026-10-08 00:00:00','Proxim'),('T-8ecf302a','L-a620be60','2026-04-08 00:00:00','2026-10-18 00:00:00','Proxim'),('T-c188f3b1','L-a620be60','2026-04-06 00:00:00','2026-10-06 00:00:00','Proxim'),('T-d1e40e03','L-be36f0c6','2026-04-08 00:00:00','2026-10-10 00:00:00','Proxim');
/*!40000 ALTER TABLE `Temporada` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Usuari`
--

DROP TABLE IF EXISTS `Usuari`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Usuari` (
  `identificador` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(100) NOT NULL,
  `contrasenya` varchar(255) NOT NULL,
  `data_registre` date NOT NULL,
  `correu_electronic` varchar(150) NOT NULL,
  `Tipus` varchar(50) NOT NULL,
  PRIMARY KEY (`identificador`),
  UNIQUE KEY `correu_electronic` (`correu_electronic`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Usuari`
--

LOCK TABLES `Usuari` WRITE;
/*!40000 ALTER TABLE `Usuari` DISABLE KEYS */;
INSERT INTO `Usuari` VALUES (1,'Gerard','1234','2026-03-31','gadmin@gmail.com','Estudiant'),(2,'administrador','1234','2026-03-31','administrador','Administrador'),(3,'capita','1234','2026-03-31','capita@gmail.com','Capita'),(4,'dani','1234','2026-03-31','dani@gmail.com','Administrador'),(5,'jordi','1234','2026-03-31','capitajordi@gmail.com','Capita'),(6,'mafe','1234','2026-03-31','mafe@gmail.com','Administrador'),(7,'jordi','1234','2026-03-31','jordicapita@gmail.com','Capita'),(8,'Gerard','1234','2026-04-01','capita@gmail,com','Capita'),(9,'admin','1234','2026-04-01','admin@gmail.com','Administrador'),(11,'jose','1234','2026-04-01','josecapita@gmail.com','Capita'),(12,'David','1234','2026-04-02','david@gmail.com','Estudiant'),(13,'mec','1234','2026-04-02','mec@gmail.com','Capita'),(15,'dani','d','2026-04-02','d@gmail.com','Capita'),(17,'dani','1234','2026-04-02','admind@gmail.com','Administrador'),(18,'dani','d2','2026-04-02','d2@gmail.com','Capita'),(19,'geri','1234','2026-04-02','capitagerard@gmail.com','Capita'),(20,'67','1234','2026-04-02','67capita@gmail.com','Capita'),(21,'joel','1234','2026-04-05','joel@gmail.com','Capita'),(22,'joel','1234','2026-04-06','joeladmin@gmail.com','Administrador'),(23,'geri','1234','2026-04-08','cafe@gmail.com','Capita'),(24,'joel','1234','2026-04-08','capita2@gmail.com','Capita');
/*!40000 ALTER TABLE `Usuari` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-04-08 16:24:55
