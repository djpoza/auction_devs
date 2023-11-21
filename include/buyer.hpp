#ifndef CADMIUM_EXAMPLE_AUCTION_BUYER_HPP_
#define CADMIUM_EXAMPLE_AUCTION_BUYER_HPP_

#include <cadmium/core/modeling/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "filter.hpp"
#include "bid.hpp"	
#include "feedback.hpp"

namespace cadmium::example::auction {
	//! Coupled DEVS model of the experimental frame.
	struct buyer: public Coupled {
		Port<Feedback> in;   //!< 
		Port<Bidinfo> out;   //!< 

		/**
		 * Constructor function for the bid model.
		 * @param id ID of the bid model.
		 * @param jobPeriod Job generation period for the Generator model.
		 * @param obsTime time to wait by the Transducer before asking the Generator to stop creating Job objects.
		 */
		buyer(const std::string& id, int ID_b, double RPr, double PPrStep, double InitialPPr): Coupled(id) {
			in = addInPort<Feedback>("in");
			out = addOutPort<Bidinfo>("out");

			auto filter = addComponent<Filter>("filter_b-"+std::to_string(ID_b), ID_b); // +std::string(id)
			auto bid = addComponent<Bid>("bid-"+std::to_string(ID_b), ID_b, RPr, PPrStep, InitialPPr); //+std::string(id)
			//auto ies = addComponent<lib::IEStream<Feedback>>("file", filepath);

			addCoupling(in, filter->in);
			addCoupling(filter->out, bid->in);
			addCoupling(bid->out, out);
		}
	};
}  //namespace cadmium::example::auction

#endif //CADMIUM_EXAMPLE_AUCTION_BUYER_HPP_
