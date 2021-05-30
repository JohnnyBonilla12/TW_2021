-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 30-05-2021 a las 06:13:20
-- Versión del servidor: 10.4.17-MariaDB
-- Versión de PHP: 8.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `gas_monitor`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `alerta`
--

CREATE TABLE `alerta` (
  `id_alerta` int(11) NOT NULL,
  `fecha_hora` datetime NOT NULL,
  `valor_sensor` int(11) NOT NULL,
  `latitud` varchar(50) NOT NULL,
  `longitud` varchar(50) NOT NULL,
  `nombre_esp` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `alerta`
--

INSERT INTO `alerta` (`id_alerta`, `fecha_hora`, `valor_sensor`, `latitud`, `longitud`, `nombre_esp`) VALUES
(1, '2021-05-25 19:38:36', 514, '-19.8976', '-19.8973', 'TEST'),
(2, '2021-05-25 19:41:02', 514, '-19.8976', '-19.8973', 'TEST'),
(3, '2021-05-25 19:42:51', 514, '-19.8976', '-19.8973', 'TEST'),
(4, '2021-05-25 19:44:05', 514, '-19.8976', '-19.8973', 'TEST'),
(5, '2021-05-25 19:45:39', 514, '-19.8976', '-19.8973', 'TEST'),
(11, '2021-05-26 09:41:09', 1671, '19.552636', '-96.950224', 'JX'),
(12, '2021-05-26 09:44:20', 1658, '19.552636', '-96.950224', 'JX'),
(13, '2021-05-26 09:44:38', 1114, '19.552636', '-96.950224', 'JX'),
(14, '2021-05-26 09:56:43', 1690, '19.552636', '-96.950224', 'JX'),
(15, '2021-05-26 09:57:46', 863, '19.552636', '-96.950224', 'JX'),
(16, '2021-05-26 10:52:59', 1739, '19.552636', '-96.950224', 'JX'),
(17, '2021-05-26 10:53:51', 934, '19.552636', '-96.950224', 'JX'),
(18, '2021-05-26 11:24:39', 2001, '19.552636', '-96.950224', 'JX'),
(19, '2021-05-26 11:24:54', 2112, '19.552636', '-96.950224', 'JX'),
(20, '2021-05-26 11:25:25', 635, '19.552636', '-96.950224', 'JX'),
(21, '2021-05-26 12:15:51', 1931, '19.552636', '-96.950224', 'JX'),
(23, '2021-05-28 09:14:42', 1136, '19.552636', '-96.950224', 'JBL');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `hibernate_sequence`
--

CREATE TABLE `hibernate_sequence` (
  `next_val` bigint(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `hibernate_sequence`
--

INSERT INTO `hibernate_sequence` (`next_val`) VALUES
(6);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `alerta`
--
ALTER TABLE `alerta`
  ADD PRIMARY KEY (`id_alerta`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `alerta`
--
ALTER TABLE `alerta`
  MODIFY `id_alerta` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=24;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
