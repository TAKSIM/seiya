#ifndef SERVER_DEAL_HPP
#define SERVER_DEAL_HPP

#include "configs.hpp"
#include "error.hpp"
#include "underlying.hpp"

typedef std::map<Underlying, std::tuple<double, double>> Offers;

class Deal
{
protected:
	Underlying m_underlying;
	date m_tradeDate;
	double m_tradePrice;
	double m_amount;
	std::string m_dealID;
	Currency m_settlementCcy;

public:
	Deal(const Underlying& underlying, double tradePrice, double tradeAmount, const Currency& settlementCcy)
		: m_underlying(underlying)
		, m_tradePrice(tradePrice)
		, m_amount(tradeAmount)
		, m_settlementCcy(settlementCcy)
	{
	}

	Deal(date tradeDate, std::string dealID, const Underlying& u, double tradePrice, double tradeAmount, const Currency& settlementCcy)
		: m_tradeDate(tradeDate)
		, m_dealID(dealID)
		, m_underlying(u)
		, m_tradePrice(tradePrice)
		, m_amount(tradeAmount)
		, m_settlementCcy(settlementCcy)
	{}

	Deal(const Deal& other)
		: m_underlying(other.GetUnderlying())
		, m_tradeDate(other.TradeDate())
		, m_amount(other.TradeAmount())
		, m_dealID(other.DealID())
		, m_settlementCcy(other.SettlementCcy())
	{}
		
	virtual ~Deal()
	{
	}

	Underlying GetUnderlying() const { return m_underlying; }
	date TradeDate() const { return m_tradeDate; }
	virtual bool IsBuy() const { return m_amount >= 0; }
	std::string DealID() const { return m_dealID; }
	double TradePrice() const { return m_tradePrice; }
	double TradeAmount() const { return m_amount; }
	Currency SettlementCcy() const { return m_settlementCcy; }

	virtual double Price(MarketEnvironment mktData) const = 0;
	virtual std::list<std::tuple<Underlying, OfferType>> PricingDataRequest()
	{
		std::list<std::tuple<Underlying, OfferType>> r;
		r.push_back(std::tuple<Underlying,OfferType>(m_underlying, IsBuy() ? OfferType::Bid : OfferType::Ask));
		return r;
	}
};

class FXDeal : public Deal
{
public:
	FXDeal(const Forex& pair, double tradePrice, double tradeAmount, const Currency& settlementCcy)
		:Deal(pair, tradePrice, tradeAmount, settlementCcy)
	{}

	FXDeal(const Forex& pair, double tradePrice, double tradeAmount)
		:Deal(pair, tradePrice, tradeAmount, pair.BaseCcy())
	{}

	FXDeal(date tradeDate, const std::string& dealID, const Forex& pair, double tradePrice, double tradeAmount, const Currency& settlementCcy)
		:Deal(tradeDate, dealID, pair, tradePrice, tradeAmount, settlementCcy)
	{}

	FXDeal(date tradeDate, const std::string& dealID, const Forex& pair, double tradePrice, double tradeAmount)
		:Deal(tradeDate, dealID, pair, tradePrice, tradeAmount, pair.BaseCcy())
	{}

	virtual double Price(MarketEnvironment mktData)
	{
		bool isBuy = IsBuy();
		DataRequest r(m_underlying, (isBuy ? OfferType::Bid : OfferType::Ask));
		double snapPrice = mktData.Response(r);
		double p = (snapPrice - m_tradePrice) / snapPrice;

		bool sameDenom = (m_settlementCcy == m_underlying.SettlementCcy());
		if (sameDenom)
			return p;
		else
		{
			
		}
	}
};

#endif 