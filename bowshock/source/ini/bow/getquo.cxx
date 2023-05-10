// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cinttypes>

auto ::bow::bow::getquo(char const * * const quo,char const * * src,::zp::i8 const id) noexcept -> void {
	switch (id) {
	default:
		bow_logerr("invalid quote identifier (%" PRIX8 ")",id);
		[[fallthrough]];
	case 0x0u:
		*quo = "You gotta be heaven to see heaven.";
		*src = "Jim Carrey";
		break;
	case 0x1u:
		*quo = "Though it's the end of the world, don't blame yourself, now.";
		*src = "Porter Robinson";
		break;
	case 0x2u:
		*quo = "The future will be better tomorrow.";
		*src = "Dan Quayle";
		break;
	case 0x3u:
		*quo = "Sir, an equation has no meaning for me unless it expresses a thought of god.";
		*src = "Srinivasa Ramanujan Aiyangar";
		break;
	case 0x4u:
		*quo = "Amīcus Platō amīcus Aristotelēs magis amīca vēritās.";
		*src = "Isaac Newton";
		break;
	case 0x5u:
		*quo = "I have studied these things \u2013 you have not.";
		*src = "Isaac Newton";
		break;
	case 0x6u:
		*quo = "La construction d'une machine propre à exprimer tous les sons de nos paroles, avec toutes les articulations, serait sans doute une décourverte bien importante.\n... La chose ne me paraît pas impossible.";
		*src = "Leonhard Euler";
		break;
	case 0x7u:
		*quo = "In mathematics, you don't understand things, you just get used to them.";
		*src = "John von Neumann";
		break;
	case 0x8u:
		*quo = "Being a language, mathematics may be used not only to inform, but also \u2013 among other things \u2013 to seduce.";
		*src = "Benoît B. Mandelbrot";
		break;
	case 0x9u:
		*quo = "The real question is not whether machines think, but whether men do.";
		*src = "Burrhus Frederic Skinner";
		break;
	case 0xAu:
		*quo = "Those who are not shocked when they first come across quantum theory cannot possibly have understood it.";
		*src = "Niels Henrik David Bohr";
		break;
	case 0xBu:
		*quo = "Every sentence I utter must be understood not as an affirmation, but as a question.";
		*src = "Niels Henrik David Bohr";
		break;
	case 0xCu:
		*quo = "We will now discuss in a little more detail the struggle for existence.";
		*src = "Charles Robert Darwin";
		break;
	case 0xDu:
		*quo = "Nam et ipsa scientia potestas est.";
		*src = "Francis Bacon";
		break;
	case 0xEu:
		*quo = "We don't know a millionth of one percent about anything.";
		*src = "Thomas Alva Edison";
		break;
	case 0xFu:
		*quo = "My goal is simple. It is a complete understanding of the universe, why it is as it is, and why it exists at all.";
		*src = "Stephen William Hawking";
		break;
	case 0x10u:
		*quo = "Equipped with his five senses, man explores the universe around him and calls the adventure Science.";
		*src = "Edwin Powell Hubble";
		break;
	case 0x11u:
		*quo = "I can say this: I believe that the human mind, or even the mind of a cat, is more interesting in its complexity than an entire galaxy if it is devoid of life.";
		*src = "Martin Gardner";
		break;
	case 0x12u:
		*quo = "I'm always right. This time I'm just more right than usual.";
		*src = "Linus Benedict Torvalds";
		break;
	case 0x13u:
		*quo = "I'm an instant tar. Just add water and stir.";
		*src = "David Robert Jones";
		break;
	case 0x14u:
		*quo = "Don't waste the Earth \u2013 it is our jewel!";
		*src = "Buzz Eugene Aldrin";
		break;
	case 0x15u:
		*quo = "I think we're going to the moon because it's in the nature of the human being to face challenges.";
		*src = "Neil Alden Armstrong";
		break;
	case 0x16u:
		*quo = "A hacker is someone who enjoys playful cleverness \u2013 not necessarily with computers.";
		*src = "Richard Matthew Stallman";
		break;
	case 0x17u:
		*quo = "So Einstein was wrong when he said \"God noes not play dice.\". Consideration of black holes suggests, not only that God does play dice, but that he sometimes confuses us by throwing them where they can't be seen.";
		*src = "Stephen William Hawking";
		break;
	case 0x18u:
		*quo = "I'm a blacktar.";
		*src = "David Robert Jones";
		break;
	case 0x19u:
		*quo = "Sooner or later, we must expand life beyond our little blue mud ball \u2013 or go extinct.";
		*src = "Elon Reeve Musk";
		break;
	case 0x1Au:
		*quo = "I would like to die on Mars \u2013 just not on impact.";
		*src = "Elon Reeve Musk";
		break;
	case 0x1Bu:
		*quo = "The web does not just connect computers; it connects people.";
		*src = "Timothy John Berners-Lee";
		break;
	case 0x1Cu:
		*quo = "Can digital computers think?";
		*src = "Alan Mathison Turing";
		break;
	case 0x1Du:
		*quo = "That's one small step for a man, one giant leap for mankind.";
		*src = "Neil Alden Armstrong";
		break;
	case 0x1Eu:
		*quo = "If you think it's simple, then you have misunderstood the problem.";
		*src = "Bjarne Stroustrup";
		break;
	case 0x1Fu:
		*quo = "Controlling complexity is the essence of computer programming.";
		*src = "Brian Wilson Kerningham";
		break;
	case 0x20u:
		*quo = "I have always wished for my computer to be as easy to use as my telephone.\nMy wish has come true because I can no longer figure out how to use my telephone.";
		*src = "Bjarne Stroustrup";
		break;
	case 0x21u:
		*quo = "There is no mathematical sibstitute for philosophy.";
		*src = "Saul Aaron Kripke";
		break;
	case 0x22u:
		*quo = "Biology is engineering.";
		*src = "Daniel Clement Dennett III";
		break;
	case 0x23u:
		*quo = "The universe is under no obligation to make sense to you.";
		*src = "Neil deGrasse Tyson";
		break;
	}
}
