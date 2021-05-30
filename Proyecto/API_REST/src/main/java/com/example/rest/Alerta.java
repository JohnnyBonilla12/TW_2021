package com.example.rest;

import javax.persistence.Entity;
import javax.persistence.Id;

@Entity
public class Alerta {
    @Id
    private Integer id_alerta;
    private String fecha_hora;
    private Integer valor_sensor;
    private String latitud;
    private String longitud;
    private String nombreEsp;

    public Alerta(){
        this.id_alerta = 0;
        this.fecha_hora = "";
        this.valor_sensor = 0;
        this.latitud = "";
        this.longitud = "";
        this.nombreEsp = "";
    }

    public Integer getId_alerta() {
        return id_alerta;
    }
    public void setId_alerta(Integer id_alerta) {
        this.id_alerta = id_alerta;
    }

    public String getFecha_hora() {
        return fecha_hora;
    }

    public void setFecha_hora(String fecha_hora) {
        this.fecha_hora = fecha_hora;
    }

    public Integer getValor_sensor() {
        return valor_sensor;
    }
    public void setValor_sensor(Integer valor_sensor) {
        this.valor_sensor = valor_sensor;
    }

    public String getLatitud() {
        return latitud;
    }
    public void setLatitud(String latitud) {
        this.latitud = latitud;
    }

    public String getLongitud() {
        return longitud;
    }
    public void setLongitud(String longitud) {
        this.longitud = longitud;
    }

    public String getnombreEsp() {
        return nombreEsp;
    }
    public void setnombreEsp(String nombreEsp) {
        this.nombreEsp = nombreEsp;
    }

    @Override
    public String toString(){
        String mensaje =    this.fecha_hora + ", " + this.valor_sensor + ", " + 
                            this.latitud + ", " + this.longitud + ", " + this.nombreEsp;
        return mensaje;
    }
}
