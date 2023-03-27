#define bow_sym "init"

#include <bow/gfx.h>
#include <bow/sav.h>

#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <zap/str.h>

bow_stat bow_loop(bow_playdat * playdat);

sig_atomic_t volatile bow_gotintr;

static bool bow_getquot(char const * * quot,char const * * src,zap_i8 id);

static void bow_intrhandl(int const sig) {
	signal(sig,bow_intrhandl); // Ignore the return value.
	bow_gotintr = 0x1;
}

int main(int const argc,char const * const * argv) {
	char const * const prognm = argv[0x0u];
	if (argc > 0x1) {
		char const * const * const stop = argv+(zap_sz)argc;
		while (argv++ != stop) {
			char const * const arg = *argv;
			if (zap_streq(arg,"--help")) {
				bow_rawlog(
					"\n"
					"bowshock %" PRIXLEAST64 ".%" PRIXLEAST64 "\n"
					"Copyright 2022-2023 Gabriel Jensen\n"
					"\n"
					"Usage: %s [savefile]\n"
					"\n",
					bow_vermaj,bow_vermin,prognm);
				return EXIT_SUCCESS;
			}
			bow_logerr("invalid parameter \"%s\"",arg);
		}
	}
	srand((unsigned int)time(nullptr));
	{
		zap_i8 const quotid = (unsigned int)rand() % 0x21u;
		char const * quot;
		char const * src;
		if (bow_getquot(&quot,&src,quotid)) {
			bow_logerr("invalid quote identifier (%" PRIXLEAST8 ")",quotid);
			bow_getquot(&quot,&src,0x0u);
		}
		bow_rawlog("\n%s\n\u2014 %s\n\n",quot,src);
	}
	bow_rawlog("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIXLEAST64 ".%" PRIXLEAST64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",bow_vermaj,bow_vermin);
	bow_log("initialising");
	bow_dbglog("debug mode is enabled");
	bow_gotintr = 0x0;
	if (signal(SIGINT,bow_intrhandl) == SIG_ERR) {
		bow_log("unable to set signal handler");
		bow_quit(bow_stat_err);
	}
	char const * savpth;
	bow_playdat playdat;
	bow_initdat(&playdat,&savpth);
	bow_initgfx();
	bow_loop(&playdat);
	bow_sav(savpth,&playdat);
	bow_quit(bow_stat_ok);
}

static bool bow_getquot(char const * * const quot,char const * * src,zap_i8 const id) {
	switch (id) {
	default:
		return true;
	case 0x0u:
		*quot = "You gotta be heaven to see heaven.";
		*src = "Jim Carrey";
		break;
	case 0x1u:
		*quot = "Though it's the end of the world, don't blame yourself, now.";
		*src = "Porter Robinson";
		break;
	case 0x2u:
		*quot = "The future will be better tomorrow.";
		*src = "Dan Quayle";
		break;
	case 0x3u:
		*quot = "Sir, an equation has no meaning for me unless it expresses a thought of god.";
		*src = "Srinivasa Ramanujan Aiyangar";
		break;
	case 0x4u:
		*quot = "Amīcus Platō amīcus Aristotelēs magis amīca vēritās.";
		*src = "Isaac Newton";
		break;
	case 0x5u:
		*quot = "I have studied these things \u2013 you have not.";
		*src = "Isaac Newton";
		break;
	case 0x6u:
		*quot = "La construction d'une machine propre à exprimer tous les sons de nos paroles, avec toutes les articulations, serait sans doute une décourverte bien importante.\n... La chose ne me paraît pas impossible.";
		*src = "Leonhard Euler";
		break;
	case 0x7u:
		*quot = "In mathematics, you don't understand things, you just get used to them.";
		*src = "John von Neumann";
		break;
	case 0x8u:
		*quot = "Being a language, mathematics may be used not only to inform, but also \u2013 among other things \u2013 to seduce.";
		*src = "Benoît B. Mandelbrot";
		break;
	case 0x9u:
		*quot = "The real question is not whether machines think, but whether men do.";
		*src = "Burrhus Frederic Skinner";
		break;
	case 0xAu:
		*quot = "Those who are not shocked when they first come across quantum theory cannot possibly have understood it.";
		*src = "Niels Henrik David Bohr";
		break;
	case 0xBu:
		*quot = "Every sentence I utter must be understood not as an affirmation, but as a question.";
		*src = "Niels Henrik David Bohr";
		break;
	case 0xCu:
		*quot = "We will now discuss in a little more detail the struggle for existence.";
		*src = "Charles Robert Darwin";
		break;
	case 0xDu:
		*quot = "Nam et ipsa scientia potestas est.";
		*src = "Francis Bacon";
		break;
	case 0xEu:
		*quot = "We don't know a millionth of one percent about anything.";
		*src = "Thomas Alva Edison";
		break;
	case 0xFu:
		*quot = "My goal is simple. It is a complete understanding of the universe, why it is as it is, and why it exists at all.";
		*src = "Stephen William Hawking";
		break;
	case 0x10u:
		*quot = "Equipped with his five senses, man explores the universe around him and calls the adventure Science.";
		*src = "Edwin Powell Hubble";
		break;
	case 0x11u:
		*quot = "I can say this: I believe that the human mind, or even the mind of a cat, is more interesting in its complexity than an entire galaxy if it is devoid of life.";
		*src = "Martin Gardner";
		break;
	case 0x12u:
		*quot = "I'm always right. This time I'm just more right than usual.";
		*src = "Linus Benedict Torvalds";
		break;
	case 0x13u:
		*quot = "I'm an instant star. Just add water and stir.";
		*src = "David Robert Jones";
		break;
	case 0x14u:
		*quot = "Don't waste the Earth \u2013 it is our jewel!";
		*src = "Buzz Eugene Aldrin";
		break;
	case 0x15u:
		*quot = "I think we're going to the moon because it's in the nature of the human being to face challenges.";
		*src = "Neil Alden Armstrong";
		break;
	case 0x16u:
		*quot = "A hacker is someone who enjoys playful cleverness \u2013 not necessarily with computers.";
		*src = "Richard Matthew Stallman";
		break;
	case 0x17u:
		*quot = "So Einstein was wrong when he said \"God noes not play dice.\". Consideration of black holes suggests, not only that God does play dice, but that he sometimes confuses us by throwing them where they can't be seen.";
		*src = "Stephen William Hawking";
		break;
	case 0x18u:
		*quot = "I'm a blackstar.";
		*src = "David Robert Jones";
		break;
	case 0x19u:
		*quot = "Sooner or later, we must expand life beyond our little blue mud ball \u2013 or go extinct.";
		*src = "Elon Reeve Musk";
		break;
	case 0x1Au:
		*quot = "I would like to die on Mars \u2013 just not on impact.";
		*src = "Elon Reeve Musk";
		break;
	case 0x1Bu:
		*quot = "The web does not just connect computers; it connects people.";
		*src = "Timothy John Berners-Lee";
		break;
	case 0x1Cu:
		*quot = "Can digital computers think?";
		*src = "Alan Mathison Turing";
		break;
	case 0x1Du:
		*quot = "That's one small step for a man, one giant leap for mankind.";
		*src = "Neil Alden Armstrong";
		break;
	case 0x1Eu:
		*quot = "If you think it's simple, then you have misunderstood the problem.";
		*src = "Bjarne Stroustrup";
		break;
	case 0x1Fu:
		*quot = "Controlling complexity is the essence of computer programming.";
		*src = "Brian Wilson Kerningham";
		break;
	case 0x20u:
		*quot = "I have always wished for my computer to be as easy to use as my telephone. My wish has come true because I can no longer figure out how to use my telephone.";
		*src = "Bjarne Stroustrup";
		break;
	}
	return false;
}
