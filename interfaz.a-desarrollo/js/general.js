// Actualizacion de datos.
$(document).ready(function(){
	// Huecos datos.
	
	var dato_pet=$('#pet');
	var dato_eet=$('#eet');
	var dato_pee=$('#pee');
	var dato_eee=$('#eee');
	
	var dato_peth=$('#peth');
	var dato_eeth=$('#eeth');
	var dato_peeh=$('#peeh');
	var dato_eeeh=$('#eeeh');
	
	var dato_cantidad=$('#cantidad');
	
	// Actualiza los datos mostrados en los huecos.
	var actualizar=function(datos){
		// Formateado.
		
		for(var dato_clave in datos){
			if(isNaN(datos[dato_clave])){
				continue;
			}
			
			if(window.Intl && Intl.NumberFormat){
				datos[dato_clave]=new Intl.NumberFormat('es-ES').format(datos[dato_clave]);
			}
		}
		
		// Total.
		
		var termica_energia_total_valor=datos.termica_energia_total_valor;
		var termica_energia_total_unidades=datos.termica_energia_total_unidades;
		var termica_energia_total=termica_energia_total_valor+' '+termica_energia_total_unidades;
		
		var termica_co2_total_valor=datos.termica_co2_total_valor;
		var termica_co2_total_unidades=datos.termica_co2_total_unidades;
		var termica_co2_total=termica_co2_total_valor+' '+termica_co2_total_unidades;
		
		var electrica_energia_total_valor=datos.electrica_energia_total_valor;
		var electrica_energia_total_unidades=datos.electrica_energia_total_unidades;
		var electrica_energia_total=electrica_energia_total_valor+' '+electrica_energia_total_unidades;
		
		var electrica_co2_total_valor=datos.electrica_co2_total_valor;
		var electrica_co2_total_unidades=datos.electrica_co2_total_unidades;
		var electrica_co2_total=electrica_co2_total_valor+' '+electrica_co2_total_unidades;
		
		var arboles_total_valor=datos.arboles_total_valor;
		var arboles_total=arboles_total_valor;
		
		// Hoy.
		
		var termica_energia_hoy_valor=datos.termica_energia_hoy_valor;
		var termica_energia_hoy_unidades=datos.termica_energia_hoy_unidades;
		var termica_energia_hoy=termica_energia_hoy_valor+' '+termica_energia_hoy_unidades;
		
		var termica_co2_hoy_valor=datos.termica_co2_hoy_valor;
		var termica_co2_hoy_unidades=datos.termica_co2_hoy_unidades;
		var termica_co2_hoy=termica_co2_hoy_valor+' '+termica_co2_hoy_unidades;
		
		var electrica_energia_hoy_valor=datos.electrica_energia_hoy_valor;
		var electrica_energia_hoy_unidades=datos.electrica_energia_hoy_unidades;
		var electrica_energia_hoy=electrica_energia_hoy_valor+' '+electrica_energia_hoy_unidades;
		
		var electrica_co2_hoy_valor=datos.electrica_co2_hoy_valor;
		var electrica_co2_hoy_unidades=datos.electrica_co2_hoy_unidades;
		var electrica_co2_hoy=electrica_co2_hoy_valor+' '+electrica_co2_hoy_unidades;
		
		// Actualizado interfaz.
		
		$(dato_pet).text(termica_energia_total);
		$(dato_eet).text(termica_co2_total);
		$(dato_pee).text(electrica_energia_total);
		$(dato_eee).text(electrica_co2_total);
		$(dato_cantidad).text(arboles_total);
		
		$(dato_peth).text(termica_energia_hoy);
		$(dato_eeth).text(termica_co2_hoy);
		$(dato_peeh).text(electrica_energia_hoy);
		$(dato_eeeh).text(electrica_co2_hoy);
	};
	var actualizar_datos=function(){
		actualizar({
			'termica_energia_total_valor':25000000,
			'termica_energia_total_unidades':'KWh',
			'termica_co2_total_valor':12000,
			'termica_co2_total_unidades':'Tn',
			'electrica_energia_total_valor':5000000,
			'electrica_energia_total_unidades':'KWh',
			'electrica_co2_total_valor':20000,
			'electrica_co2_total_unidades':'Tn',
			'arboles_total_valor':21013,
			'termica_energia_hoy_valor':25000,
			'termica_energia_hoy_unidades':'KWh',
			'termica_co2_hoy_valor':2.5,
			'termica_co2_hoy_unidades':'Kg',
			'electrica_energia_hoy_valor':5000,
			'electrica_energia_hoy_unidades':'KWh',
			'electrica_co2_hoy_valor':1.5,
			'electrica_co2_hoy_unidades':'Kg',
		});
	};
	
	// Recupera los datos y los actualiza
	var recuperar=function(){
		var peticion_url='datos.json.php';
		
		var peticion_url_parametros={
		};
		
		var peticion_parametros={
			'type':'GET',
			'cache':false,
			'data':peticion_url_parametros,
			'dataType':'json',
		};
		
		var peticion=$.ajax(peticion_url, peticion_parametros);
		
		var peticion_completado=function(respuesta,estado,peticion){
			// Comprobamos el estado de la peticion.
			if(['success'].indexOf(estado)<0){
				console.error('No se ha completado correctamente la peticion');
			}
			
			// Anotamos y actualizamos los parametros.
			
			actualizar(respuesta);
		};
		
		var peticion_error=function(peticion,estado,mensaje){
			console.error('Se ha producido un error en la peticion');
		};
		
		// Relizamos la peticion.
		return $.when(peticion).done(peticion_completado).fail(peticion_error);
	};
	
	// Autorecarga.
	
	var autorecarga_intervalo=5*60+0;
	var autorecarga_intervalo=0*60+5;
	
	window.setInterval(function(){
		recuperar();
	},autorecarga_intervalo*1000);
	
	recuperar();
	
window.actualizar=actualizar;
window.actualizar_datos=actualizar_datos;
window.recuperar=recuperar;
});
