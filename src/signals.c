
#include "../include/minishell.h"
#include <signals.h>

volatile int g_signal = 0;


static void	sigint_handler(int sig)
{
	g_signal = sig;
	rl_done = 1;
}
/*✔ Guarda la señal en la global
✔ rl_done = 1 hace que readline termine inmediatamente → perfecto*/
/*static void	sigquit_handler(int sig)
{
	(void)sig;
} - no needed */

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);//sigquit_handler);
}
/* Configuración de señales. Esto es aún mejor: hace que Ctrl-\ literalmente no haga nada, como bash.

No necesitas ya sigquit_handler.*/
/*
Usuario pulsa Ctrl-C

sigint_handler se ejecuta

rl_done = 1 → readline termina

Vuelves al loop principal con line = NULL o con cadena vacía

Tu código detecta que g_signal == SIGINT

Limpiamos línea, imprimimos newline y refrescamos prompt

continue → va al siguiente ciclo → nuevo prompt como bash*/