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
	display *philos
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
	display *new_philo
	display *new_philo@philo->data->n_philos
	display i
end 

define init_data
	display argc
	display argv
	display new
	display *new
	display data
	display *data
end 

define init_forks
	display *data
	display *data->mutex_fork
	display i
end

define init_philo
	display i
	display *philo
	display *data
	display *forks
end

# ft_parse.c
define parse_arg
	display str
	display str[i]
	display i
	display sign
	display num
end

# ...

# GO GDB GO!
# Start at main
# break main
# run 4 410 200 200
# main
# fs cmd

# Start at init
break ft_init
run 4 410 200 200
# init
# fs cmd

# # Start at init_data
# break ft_init_data
# run "   2a33" 200 200 200
# init_data
# fs cmd

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
