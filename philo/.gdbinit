### GDB Settings 
set trace-commands on
set logging enabled on
set print pretty on
set print array on

# main.c
define main
	display argc
	display argv
	display *philos
	display philos@(*philos)->data->n_philos
end


define philosophize
	display *p
	display p->data->thread@(*p)->data->n_philos
	display i 
	display th
	display *th
end

define start_philo
	display philo
	display *philo
	display *philo->id
end

define monitor
	display philo
	display *philo
	display last_meal
	display i
end

# ft_free.c
define free
	display *philo->data->mutex_fork@(*philo)->data->n_philos
	display *philo->data
end

# ft_init.c
define init
	display philo
	display argc
	display argv
	display *data
	display **data
end 

define init_data
	display argc
	display argv
	display data
	display *data
	display **data
end 

define init_mtx
	display *data
	display **data
	display *data->mutex
	display i
end

define init_philo
	display fork
	display i
	display *data
	display *philo
	display philo[i]
	display *philo[i]
end

# ft_parse.c
define parse_arg
	display str
	display str[i]
	display i
	display sign
	display num
end

# ft_time.c
define log
	display p
	display *p
	display *str
	display ft_dtime(p->data->t_start)

end

# ...

# GO GDB GO!
# Start at main
# break main
# run 1 800 200 200 3
# main
# fs cmd

# Start at init
# break ft_init
# run 1 800 400 400 3
# init
# fs cmd

# # Start at init_data
# break ft_init_data
# run "   2a33" 200 200 200
# init_data
# fs cmd

# Start at ft_philosophixe
# break ft_philosophize
# run 3 800 200 200 3
# philosophize
# fs cmd

# Start at ft_start_philo
break ft_start_philo
run 2 800 200 200 3
start_philo
fs cmd

# break ft_init_forks
# break ft_init_philo

# Start at parse_arg
# break ft_parse_arg
# run "   2a33" 200 200 200
# parse_arg
# fs cmd

# Start at init_forks
# break ft_init_forks

# Start at init_philo
# break ft_init_philo

# Start at ft_free
break ft_free
# run "   5" 800 200 200
# free
# fs cmd

info break
info threads
