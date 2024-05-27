### GDB Settings 
set trace-commands on
set logging enabled on
set print pretty on
set print array on

# main.c
define main
	display argc
	display *argv@argc
	display data
	display *data
	display *philos
end

define philosophize
	display *philos
end

define children
	display *philo
	display *curr_philo
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

# ft_init_philo.c
define free_philo
	display philo
	display tmp
	display *tmp
	display next
	display *next
	display *next->next
end


define init_philo
	display data
	display *data
	display philo
	display *philo
	display new
	display *new
	display i
end

# ft_init.c
define init
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

define init_sem
	display *data
	display *data->n_philos
end

# ...

# GO GDB GO!
# Start at main
break main
run 1 800 200 200 7
main
fs cmd

# Break at ft_children
# break ft_children
# run 1 800 200 200 7
# children
# fs cmd

# Break before free
# break main
# break 48
# run 3 800 200 200 7
# main
# fs cmd

info break
info threads
