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
end

define children
	display *philo
	display new
	display i
end

define set_sem_t
	display *philo
end

define free
	display to_del
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
# break main
# run 300 800 200 200 7
# main
# fs cmd

# Break before free
# break main
# break 48
# run 3 800 200 200 7
# main
# fs cmd

# Break at ft_children
break ft_children
run 3 800 200 200 7
children
fs cmd
