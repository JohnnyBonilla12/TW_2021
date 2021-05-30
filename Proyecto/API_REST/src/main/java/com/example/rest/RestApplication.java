package com.example.rest;

import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;

import com.google.gson.Gson;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;


@RestController
@SpringBootApplication
public class RestApplication {
	@Autowired
	private Interface_CRUD interface_crud;

	public static void main(String[] args) {
		SpringApplication.run(RestApplication.class, args);
	}

	@RequestMapping(method = RequestMethod.POST, value = "/gas/registrar")
	public String registrar_Alerta(	@RequestParam(required = true, value="valor") Integer valor, 
									@RequestParam(required = true, value="latitud") String latitud,
									@RequestParam(required = true, value="longitud") String longitud,
									@RequestParam(required = true, value="nombre_esp") String nombre_esp)
	{
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");  
		LocalDateTime now = LocalDateTime.now(); 
		String fecha_hora = dtf.format(now);
		Alerta alerta = new Alerta();
		alerta.setFecha_hora(fecha_hora);
		alerta.setValor_sensor(valor);
		alerta.setLatitud(latitud);
		alerta.setLongitud(longitud);
		alerta.setnombreEsp(nombre_esp);
		interface_crud.save(alerta);
		return new Gson().toJson(alerta);
	}
	
	@RequestMapping(method = RequestMethod.GET, value = "/gas/historial")
	public Iterable<Alerta> ver_Historial (@RequestParam(required = true, value="nombre_esp") String nombre_esp){
		Iterable<Alerta> historial =  interface_crud.findAllBynombreEsp(nombre_esp);
		return historial;
	}

	@RequestMapping(method = RequestMethod.PUT, value = "/gas/cambiarESP32")
	public Iterable<Alerta> cambiar_NombreESP32( 	@RequestParam(required = true, value="nombre_esp") String nombre_esp,
													@RequestParam(required = true, value="nuevo") String nuevo)
	{
		Iterable<Alerta> alertasbyNombre = interface_crud.findAllBynombreEsp(nombre_esp);
		for (Alerta alerta : alertasbyNombre) {
			alerta.setnombreEsp(nuevo);
			interface_crud.save(alerta);
		}
		return alertasbyNombre;	
	}

	@RequestMapping(method = RequestMethod.DELETE, value = "/gas/borrarAlerta")
	public String borrar_Alerta(@RequestParam(required = true, value="id_alerta")Integer id_alerta){
		interface_crud.deleteById(id_alerta);
		return "Borrado Correctamente";
	}
}