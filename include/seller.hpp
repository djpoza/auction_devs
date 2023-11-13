#ifndef CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_
#define CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_

#include <cadmium/core/modeling/atomic.hpp>
#include <iostream>
#include "feedback.hpp"
#include "bidinfo.hpp"

namespace cadmium::example::auction {
	//! Class for representing the Generator DEVS model state.
	struct SellerState {
		//double sigma;  //!< 
		bool Notify;  //!< .
		double AskPr;  //!< True/False variable inputted from the auctioneer.

		//! Constructor function. It sets all the attributes to 0.
		SellerState(double x): Notify(true), AskPr(x) {} 
	};

	/**
	 * Insertion operator for GeneratorState objects. It only displays the value of jobCount.
	 * @param out output stream.
	 * @param s state to be represented in the output stream.
	 * @return output stream with jobCount already inserted.
	 */
	std::ostream& operator<<(std::ostream& out, const SellerState& s) {
		out << "{" << s.Notify <<"," << s.AskPr << "}";
		return out;
	}

	//! Atomic DEVS model of a Job generator.
	class Seller : public Atomic<SellerState> { //! Atomic models MUST inherit from the cadmium::Atomic<S> class
	 private:
		int ID_s;                            //!< Time to wait between Job generations.
		double PCost;
		double APrStep;
		double InitialAPr;
	 public:
		Port<Feedback> in;          //!< Input Port for receiving stop generating Job objects.
		Port<Bidinfo> out;
		//BigPort<Job> outGenerated;  //!< Output Port for sending new Job objects to be processed.

		/**
		 * Constructor function for Generator DEVS model.
		 * @param id model ID.
		 * @param jobPeriod Job generation period.
		 */
		Seller(const std::string& id, int _ID, double _PCost, double _APrStep, double _InitialAPr): Atomic<SellerState>(id, SellerState(_InitialAPr)), ID_s(_ID), PCost(_PCost), APrStep(_APrStep), InitialAPr(_InitialAPr){//, jobPeriod(jobPeriod) {
			in = addInPort<Feedback>("in");
			out = addOutPort<Bidinfo>("out");
			//s.Notify = true;
			//s.PurPr = InitialPPr;
			//outGenerated = addOutBigPort<Job>("outGenerated");
		}

		/**
		 * Updates GeneratorState::clock and GeneratorState::sigma and increments GeneratorState::jobCount by one.
		 * @param s reference to the current generator model state.
		 */
		void internalTransition(SellerState& s) const override {
			if (s.Notify == true)
			{
				s.Notify = false;
			}
		}

		/**
		 * Updates GeneratorState::clock and GeneratorState::sigma.
		 * If it receives a true message via the Generator::inStop port, it passivates and stops generating Job objects.
		 * @param s reference to the current generator model state.
		 * @param e time elapsed since the last state transition function was triggered.
		 * @param x reference to the atomic model input port set.
		 */
		void externalTransition(SellerState& s, double e) const override {
			//s.sigma = std::max(s.sigma - e, 0.);
			Feedback local_in(0, false);
			//Feedback local_in;
			local_in = in->getBag().back();
			if (local_in.gotIt == false && s.AskPr - APrStep >= PCost)
			{
				s.AskPr -= APrStep;
				s.Notify = true;
			}
		}

		/**
		 * Sends a new Job that needs to be processed via the Generator::outGenerated port.
		 * @param s reference to the current generator model state.
		 * @param y reference to the atomic model output port set.
		 */
		void output(const SellerState& s) const override {
			if (s.Notify == true)
			{
				Bidinfo outmsg = {ID_s, s.AskPr};
				out->addMessage(outmsg);
				//out->addMessage(outmsg);
			}
			
			// outGenerated->addMessage(Job(s.jobCount, s.clock + s.sigma)); // TODO we could also do this
		}

		/**
		 * It returns the value of GeneratorState::sigma.
		 * @param s reference to the current generator model state.
		 * @return the sigma value.
		 */
		[[nodiscard]] double timeAdvance(const SellerState& s) const override {
			if (s.Notify == true)
			{
				return 1;
			} else {
				return std::numeric_limits<double>::infinity();
			}
			// std::numeric_limits<double>::infinity();
		}
	};
}  //namespace cadmium::example::auction

#endif //CADMIUM_EXAMPLE_AUCTION_SELLER_HPP_
