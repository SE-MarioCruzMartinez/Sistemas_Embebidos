# 10 Sistemas de tiempo real
## Equipo 05

En esta práctica se pretende manejar el sistema operativo en tiempo real (FreeRTOS) en una ESP32. El código se realiara en la plataforma Arduino cumpliendo las siguientes condiciones:

a.) Prioridades de las tareas

b.) Frecuencia de ejecución de las tareas. Algunas de ellas se ejecutarán más veces 
    que otras. que la 8 se haga tres veces
    
c.) Conclusión de las tareas. Algunas tareas terminarán antes que otras que la 7 
    se haga menos veces
    
d.) Comunicación entre tareas. Verificar cuáles son las funciones odirectivas que 
    se pueden emplear para que una tarea comunique algo a otra. Ejercitar que las comunicaciones se den después de que pasaron varias ejecuciones, por ejemplo, que la   
    tarea 3 comunique a la tarea 5 después de que la tarea 3 ha ocurrido por quinta vez. Hacer algo similar para otros casos.
    
e.) Ejercitar dos características más que crea importantes de FreeRTOS en el mismo 
    ejemplo.
    
f.) Lineas de código comentadas a detalle.

g.) Para la presentación, se empleara el monitor serial
