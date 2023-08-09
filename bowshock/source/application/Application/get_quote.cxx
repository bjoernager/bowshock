// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdint>
#include <format>
#include <stdexcept>
#include <string>
#include <tuple>

using namespace ::std::literals::string_literals;

auto bow::Application::get_quote(::std::uint8_t const identifier) -> ::std::tuple<::std::string, ::std::string> {
	::std::string quote  = ""s;
	::std::string source = ""s;

	switch (identifier) {
	default:
		throw ::std::invalid_argument(::std::format("invalid quote identifier ({})", identifier));

	case 0x0u:
		quote  = "You gotta be heaven to see heaven.";
		source = "Jim Carrey";
		break;

	case 0x1u:
		quote  = "Though it's the end of the world, don't blame yourself, now.";
		source = "Porter Robinson";
		break;

	case 0x2u:
		quote  = "The future will be better tomorrow.";
		source = "Dan Quayle";
		break;

	case 0x3u:
		quote  = "Sir, an equation has no meaning for me unless it expresses a thought of god.";
		source = "Srinivasa Ramanujan Aiyangar";
		break;

	case 0x4u:
		quote  = "Amīcus Platō amīcus Aristotelēs magis amīca vēritās.";
		source = "Isaac Newton";
		break;

	case 0x5u:
		quote  = "I have studied these things \u2013 you have not.";
		source = "Isaac Newton";
		break;

	case 0x6u:
		quote  = "La construction d'une machine propre à exprimer tous les sons de nos paroles,\n avec toutes les articulations, serait sans doute une décourverte bien\n importante.\n\u2026 La chose ne me paraît pas impossible.";
		source = "Leonhard Euler";
		break;

	case 0x7u:
		quote  = "In mathematics, you don't understand things, you just get used to them.";
		source = "John von Neumann";
		break;

	case 0x8u:
		quote  = "Being a language, mathematics may be used not only to inform, but also \u2013 among\n other things \u2013 to seduce.";
		source = "Benoît B. Mandelbrot";
		break;

	case 0x9u:
		quote  = "The real question is not whether machines think, but whether men do.";
		source = "Burrhus Frederic Skinner";
		break;

	case 0xAu:
		quote  = "Those who are not shocked when they first come across quantum theory cannot\n possibly have understood it.";
		source = "Niels Henrik David Bohr";
		break;

	case 0xBu:
		quote  = "Every sentence I utter must be understood not as an affirmation, but as a\n question.";
		source = "Niels Henrik David Bohr";
		break;

	case 0xCu:
		quote  = "We will now discuss in a little more detail the struggle for existence.";
		source = "Charles Robert Darwin";
		break;

	case 0xDu:
		quote  = "Nam et ipsa scientia potestas est.";
		source = "Francis Bacon";
		break;

	case 0xEu:
		quote  = "We don't know a millionth of one percent about anything.";
		source = "Thomas Alva Edison";
		break;

	case 0xFu:
		quote  = "My goal is simple. It is a complete understanding of the universe, why it is as\n it is, and why it exists at all.";
		source = "Stephen William Hawking";
		break;

	case 0x10u:
		quote  = "Equipped with his five senses, man explores the universe around him and calls\n the adventure Science.";
		source = "Edwin Powell Hubble";
		break;

	case 0x11u:
		quote  = "I can say this: I believe that the human mind, or even the mind of a cat, is\n more interesting in its complexity than an entire galaxy if it is devoid of\n life.";
		source = "Martin Gardner";
		break;

	case 0x12u:
		quote  = "I'm always right. This time I'm just more right than usual.";
		source = "Linus Benedict Torvalds";
		break;

	case 0x13u:
		quote  = "I'm an instant star. Just add water and stir.";
		source = "David Robert Jones";
		break;

	case 0x14u:
		quote  = "Don't waste the Earth \u2013 it is our jewel!";
		source = "Buzz Eugene Aldrin";
		break;

	case 0x15u:
		quote  = "I think we're going to the moon because it's in the nature of the human being to\n face challenges.";
		source = "Neil Alden Armstrong";
		break;

	case 0x16u:
		quote  = "A hacker is someone who enjoys playful cleverness \u2013 not necessarily with\n computers.";
		source = "Richard Matthew Stallman";
		break;

	case 0x17u:
		quote  = "So Einstein was wrong when he said \"God does not play dice.\". Consideration of\n black holes suggests, not only that God does play dice, but that he sometimes\n confuses us by throwing them where they can't be seen.";
		source = "Stephen William Hawking";
		break;

	case 0x18u:
		quote  = "I'm a blackstar.";
		source = "David Robert Jones";
		break;

	case 0x19u:
		quote  = "Sooner or later, we must expand life beyond our little blue mud ball\u2014or go\n extinct.";
		source = "Elon Reeve Musk";
		break;

	case 0x1Au:
		quote  = "I would like to die on Mars \u2013 just not on impact.";
		source = "Elon Reeve Musk";
		break;

	case 0x1Bu:
		quote  = "The web does not just connect computers; it connects people.";
		source = "Timothy John Berners-Lee";
		break;

	case 0x1Cu:
		quote  = "Can digital computers think?";
		source = "Alan Mathison Turing";
		break;

	case 0x1Du:
		quote  = "That's one small step for a man, one giant leap for mankind.";
		source = "Neil Alden Armstrong";
		break;

	case 0x1Eu:
		quote  = "If you think it's simple, then you have misunderstood the problem.";
		source = "Bjarne Stroustrup";
		break;

	case 0x1Fu:
		quote  = "Controlling complexity is the essence of computer programming.";
		source = "Brian Wilson Kerningham";
		break;

	case 0x20u:
		quote  = "I have always wished for my computer to be as easy to use as my telephone.\n My wish has come true because I can no longer figure out how to use my\n telephone.";
		source = "Bjarne Stroustrup";
		break;

	case 0x21u:
		quote  = "There is no mathematical substitute for philosophy.";
		source = "Saul Aaron Kripke";
		break;

	case 0x22u:
		quote  = "Biology is engineering.";
		source = "Daniel Clement Dennett III";
		break;

	case 0x23u:
		quote  = "The universe is under no obligation to make sense to you.";
		source = "Neil deGrasse Tyson";
		break;
	}

	return ::std::make_tuple(quote, source);
}
