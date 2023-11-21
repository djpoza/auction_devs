#ifndef CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_
#define CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_

#include "./cadmium/core/modeling/coupled.hpp"
#include <cadmium/lib/iestream.hpp>

#include "filter.hpp"
#include "ask.hpp"	
#include "feedback.hpp"

namespace cadmium::example::auction {
	//! Coupled DEVS model of the experimental frame.
	struct seller: public Coupled {
		Port<Feedback> in;   //!< 
		Port<Bidinfo> out;   //!< 

		/**
		 * Constructor function for the bid model.
		 * @param id ID of the bid model.
		 * @param jobPeriod Job generation period for the Generator model.
		 * @param obsTime time to wait by the Transducer before asking the Generator to stop creating Job objects.
		 */
		seller(const std::string& id, int ID_s, double PCost, double APrStep, double InitialAPr): Coupled(id) {
			in = addInPort<Feedback>("in");
			out = addOutPort<Bidinfo>("out");

			auto filter = addComponent<Filter>("filter_s-"+std::to_string(ID_s), ID_s); // +ID_s
			auto ask = addComponent<Ask>("ask-"+std::to_string(ID_s), ID_s, PCost, APrStep, InitialAPr); //+ID_s
			//auto ies = addComponent<lib::IEStream<Feedback>>("file", filepath);

			addCoupling(in, filter->in);
			addCoupling(filter->out, ask->in);
			addCoupling(ask->out, out);
		}
	};
}  //namespace cadmium::example::auction

#endif //CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_
