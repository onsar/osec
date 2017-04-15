<?php 
	include_once('db_config.php');
?>
{
<?php
	/* Matriz tipo $datos['nombre_agente']['hora'] */
	$query = "select tagente_datos.id_agente_modulo, nombre , datos, from_unixtime(utimestamp,'%H') as hora from tagente_datos, tagente_modulo where tagente_datos.id_agente_modulo = tagente_modulo.id_agente_modulo and utimestamp > unix_timestamp(curdate())  group by (id_agente_modulo), hour(from_unixtime(utimestamp));";
	$result = mysql_query($query);
	$datos=array();
	while ($posts_row = mysql_fetch_assoc($result))
   	{
		$datos[urlencode($posts_row['nombre'])][$posts_row['hora']]=$posts_row['datos'];
    	}
	/* Cálculos para térmica hoy*/
	$ndatos= count($datos['Temp.%26%23x20%3BAmb%26%23x20%3B1']);
        $termica_hoy=0;
        for($i=0;$i<$ndatos; $i++){
                if($i<10)
		   $hora='0'.$i;
		$termica_hoy+=$datos['Caudal']["$hora"]*(
		$datos['Temp.panel%26%23x20%3Bout']["$hora"]-
                $datos['Temp.%26%23x20%3BAmb%26%23x20%3B1']["$hora"]);
	}
	$termica_hoy*=0.01163;

	/* Cálculos para eléctrica hoy */
	$electrica_hoy=0;
	for($i=0;$i<$ndatos; $i++){
        	if($i<10)
			$hora='0'.$i;
                if(array_key_exists($hora,$datos['Inten_1']))
			$electrica_hoy+=$datos['Inten_1']["$hora"]*500/1000;
	}


?>
	"termica_energia_total_valor":<?php echo "1" ?>,
	"termica_energia_total_unidades":"KWh",
	"termica_co2_total_valor":<?php echo 12000+mt_rand(-10,10); ?>,
	"termica_co2_total_unidades":"Tn",
	"electrica_energia_total_valor":<?php echo 5000000+mt_rand(-10,10); ?>,
	"electrica_energia_total_unidades":"KWh",
	"electrica_co2_total_valor":<?php echo 20000+mt_rand(-10,10); ?>,
	"electrica_co2_total_unidades":"Tn",
	"arboles_total_valor":<?php echo 21013+mt_rand(-10,10); ?>,
	"termica_energia_hoy_valor":<?php echo $termica_hoy ?>,
	"termica_energia_hoy_unidades":"KWh",
	"termica_co2_hoy_valor":<?php echo $termica_hoy*0.252 ?>,
	"termica_co2_hoy_unidades":"Kg",
	"electrica_energia_hoy_valor":<?php echo $electrica_hoy ?>,
	"electrica_energia_hoy_unidades":"KWh",
	"electrica_co2_hoy_valor":<?php echo $electrica_hoy*0.96 ?>,
	"electrica_co2_hoy_unidades":"Kg"
}
