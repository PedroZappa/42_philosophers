### GDB Settings 
set trace-commands on
set logging enabled on
set print pretty on
set print array on

# main.c
define main
	display argc
	display *argv@argc
	display *philos
	display philos@(*philos)->n_philos
	display *philos->pid@(*philos)->n_philos
	display i
end

define philosophize
	display *philos
	display i 
end

define free
	display *to_del
	display philo
	display *philo
	display **philo
	display i
end	

# ft_init.c
define parsinit
	display argc
	display *argv@argc
	display *new
	display new@(*new)->n_philos
	display *new->pid@(*new)->n_philos
	display i
end

define init_data
	display argc
	display *argv@argc
	display *new
	display new@(*new)->n_philos
	display *new->pid@(*new)->n_philos
end

# ...

# GO GDB GO!
# Start at main
break main
run 5 80
main
fs cmd
