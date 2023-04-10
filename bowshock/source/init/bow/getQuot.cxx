// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cinttypes>

void ::bow::bow::getQuot(char const * * const quot,char const * * src,::zap::i8 const id) noexcept {
	switch (id) {
	default:
		bow_logErr("invalid quote identifier (%" PRIX8 ")",id);
		[[fallthrough]];
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
		*quot = "I have always wished for my computer to be as easy to use as my telephone.\nMy wish has come true because I can no longer figure out how to use my telephone.";
		*src = "Bjarne Stroustrup";
		break;
	case 0x21u:
		*quot = "There is no mathematical sibstitute for philosophy.";
		*src = "Saul Aaron Kripke";
		break;
	case 0x22u:
		*quot = "Biology is engineering.";
		*src = "Daniel Clement Dennett III";
		break;
	case 0x23u:
		*quot = "The universe is under no obligation to make sense to you.";
		*src = "Neil deGrasse Tyson";
		break;
	}
}
