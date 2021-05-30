package com.example.rest;

import org.springframework.data.repository.CrudRepository;

public interface Interface_CRUD extends CrudRepository<Alerta, Integer>{
    Iterable<Alerta> findAllBynombreEsp (String nombre_esp);
}