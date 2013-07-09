package com.ismole.pay;

public class MessData {
    public String title;
    public String message;
    
    public String m_order;
	public String m_product;
	public String m_productDes;
	public String m_appScheme;
	public String m_parent;
	public String m_seller;
	public String m_notifyUrl;
	public String m_alipayKey;
	public float m_price;
    
	public MessData(String title, String message) {
		super();
		this.title = title;
		this.message = message;
	}
	
	public void setAlixData(String order, 
						String product, 
						String productDes, 
						String appScheme, 
						String parent, 
						String seller, 
						String notifyUrl,
						String aplipaykey, 
						float  price)
	{
		m_order = order;
		m_product = product;
		m_productDes = productDes;
		m_appScheme = appScheme;
		m_parent = parent;
		m_seller = seller;
		m_notifyUrl = notifyUrl;
		m_alipayKey = aplipaykey;
		m_price = price;
	}
    
}
