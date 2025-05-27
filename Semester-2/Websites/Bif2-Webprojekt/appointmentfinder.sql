-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 22, 2024 at 10:42 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `appointmentfinder`
--

-- --------------------------------------------------------

--
-- Table structure for table `appointments`
--

CREATE TABLE `appointments` (
  `ID` int(255) NOT NULL,
  `Title` varchar(255) NOT NULL,
  `Location` varchar(255) NOT NULL,
  `EndDate` date NOT NULL,
  `Description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `appointments`
--

INSERT INTO `appointments` (`ID`, `Title`, `Location`, `EndDate`, `Description`) VALUES
(1, 'Saufen', 'Wien', '2024-04-20', 'gemma pratersauna!'),
(2, 'Kino', 'Wien', '2024-05-12', 'Bock mal wieder auf Leinwand');

-- --------------------------------------------------------

--
-- Table structure for table `hasvoted`
--

CREATE TABLE `hasvoted` (
  `ID` int(255) NOT NULL,
  `ForeignDate` int(255) NOT NULL,
  `VotedName` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `hasvoted`
--

INSERT INTO `hasvoted` (`ID`, `ForeignDate`, `VotedName`) VALUES
(1, 3, 'Andor'),
(2, 2, 'Andor'),
(3, 1, 'Andor');

-- --------------------------------------------------------

--
-- Table structure for table `optiondate`
--

CREATE TABLE `optiondate` (
  `ID` int(255) NOT NULL,
  `AppointmentID` int(255) NOT NULL,
  `StartTime` time NOT NULL,
  `EndTime` time NOT NULL,
  `Date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `optiondate`
--

INSERT INTO `optiondate` (`ID`, `AppointmentID`, `StartTime`, `EndTime`, `Date`) VALUES
(1, 2, '12:52:00', '14:52:00', '2024-04-24'),
(2, 2, '17:52:00', '20:52:00', '2024-04-24'),
(3, 2, '21:53:00', '23:52:00', '2024-04-27');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `ID` int(255) NOT NULL,
  `AppID` int(255) NOT NULL,
  `Name` varchar(255) NOT NULL,
  `Comment` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`ID`, `AppID`, `Name`, `Comment`) VALUES
(11, 2, 'Andor', 'Bei mir gehen alle tage^^');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `appointments`
--
ALTER TABLE `appointments`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `hasvoted`
--
ALTER TABLE `hasvoted`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `ForeignDate` (`ForeignDate`),
  ADD KEY `ForeignUser` (`VotedName`);

--
-- Indexes for table `optiondate`
--
ALTER TABLE `optiondate`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `AppointmentID` (`AppointmentID`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `AppID` (`AppID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `appointments`
--
ALTER TABLE `appointments`
  MODIFY `ID` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `hasvoted`
--
ALTER TABLE `hasvoted`
  MODIFY `ID` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `optiondate`
--
ALTER TABLE `optiondate`
  MODIFY `ID` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `ID` int(255) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `hasvoted`
--
ALTER TABLE `hasvoted`
  ADD CONSTRAINT `ForeignDate` FOREIGN KEY (`ForeignDate`) REFERENCES `optiondate` (`ID`);

--
-- Constraints for table `optiondate`
--
ALTER TABLE `optiondate`
  ADD CONSTRAINT `AppointmentID` FOREIGN KEY (`AppointmentID`) REFERENCES `appointments` (`ID`);

--
-- Constraints for table `user`
--
ALTER TABLE `user`
  ADD CONSTRAINT `AppID` FOREIGN KEY (`AppID`) REFERENCES `appointments` (`ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
