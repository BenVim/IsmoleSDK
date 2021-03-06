package com.ismole.pay;
import org.cocos2dx.lib.Cocos2dxActivity;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class Test extends Cocos2dxActivity {

	static String TAG = "Pay";
	private ProgressDialog mProgress = null;
	private String m_parent;
	private String m_seller;
	private String m_private;
	private Button btn;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Intent i = getIntent(); 
		
		String order = i.getStringExtra("order");
		String product = i.getStringExtra("product");
		String productDes = i.getStringExtra("productDes");
		String appScheme = i.getStringExtra("appScheme");
		String parent = i.getStringExtra("parent");
		String seller = i.getStringExtra("seller");
		String notifyUrl = i.getStringExtra("notifyUrl");
		String alipayKey = i.getStringExtra("alipayKey");
		float price = i.getIntExtra("price", 0);

//		Log.e("order", order);
//		Log.e("product", product);
//		Log.e("productDes", productDes);
//		Log.e("appScheme", appScheme);
//		Log.e("parent", parent);
//		Log.e("seller", seller);
//		Log.e("notifyUrl", notifyUrl);
//		Log.e("alipayKey", alipayKey);
		//Log.e("price", String.valueOf(price));

		m_parent = parent;
		m_seller = seller;
		m_private = alipayKey;
		//
		setContentView(R.layout.activity_alix_pay_dialog);
		
		// check to see if the MobileSecurePay is already installed.
				// 检测安全支付服务是否安装
				MobileSecurePayHelper mspHelper = new MobileSecurePayHelper(this);
				boolean isMobile_spExist = mspHelper.detectMobile_sp();
				if (!isMobile_spExist)
					return;
				// check some info.
				// 检测配置信息
				if (!checkInfo()) {
					BaseHelper
							.showDialog(
									Test.this,
									"提示",
									"缺少partner或者seller，请在src/com/alipay/android/appDemo4/PartnerConfig.java中增加。",
									R.drawable.infoicon);
					return;
				}
				// start pay for this order.
				// 根据订单信息开始进行支付
				try {
					// prepare the order info.
					// 准备订单信息
					String orderInfo = "partner=" + "\"" + parent + "\"";
					orderInfo += "&";
					orderInfo += "seller=" + "\"" + seller + "\"";
					orderInfo += "&";
					orderInfo += "out_trade_no=" + "\"" + order + "\"";
					orderInfo += "&";
					orderInfo += "subject=" + "\"" + product + "\"";
					orderInfo += "&";
					orderInfo += "body=" + "\"" + productDes + "\"";
					orderInfo += "&";
					orderInfo += "total_fee=" + "\"" + price + "\"";
					orderInfo += "&";
					orderInfo += "notify_url=" + "\"" + notifyUrl + "\"";
					
					// 这里根据签名方式对订单信息进行签名
					String signType = getSignType();
					String strsign = sign(signType, orderInfo);
					Log.v("sign:", strsign);
					
					// 对签名进行编码
					strsign = URLEncoder.encode(strsign);
					// 组装好参数
					String info = orderInfo + "&sign=" + "\"" + strsign + "\"" + "&"
							+ getSignType();
					Log.v("orderInfo:", info);
					// start the pay.
					// 调用pay方法进行支付
					MobileSecurePayer msp = new MobileSecurePayer();
					boolean bRet = msp.pay(info, mHandler, AlixId.RQF_PAY, this);
					Log.e("TestLog", "Paying....");
					if (bRet) {
						// show the progress bar to indicate that we have started
						// paying.
						// 显示“正在支付”进度条
						closeProgress();
						mProgress = BaseHelper.showProgress(this, null, "正在支付", false, true);
					} else
						;
				} catch (Exception ex) {
					Toast.makeText(Test.this, R.string.remote_call_failed,
							Toast.LENGTH_SHORT).show();
				}
	
//		btn = (Button) findViewById(R.id.button1);
//		btn.setOnClickListener(new OnClickListener()
//		{
//          public void onClick(View v)
//          {
//        	  Test.this.finish();
////         	 Intent itent=new Intent();
////              itent.setClass(Test.this, Pay.class);
//              //startActivity(itent);
////              //如果不关闭当前的会出现好多个页面
//              
//          }
//		});
 
	}
	
	String getOrderInfo(int position) {
		String strOrderInfo = "partner=" + "\"" + PartnerConfig.PARTNER + "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "seller=" + "\"" + PartnerConfig.SELLER + "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "out_trade_no=" + "\"" + getOutTradeNo() + "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "subject=" + "\"" + product
//				+ "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "body=" + "\"" + mproductlist.get(position).body + "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "total_fee=" + "\""
//				+ mproductlist.get(position).price.replace("一口价:", "") + "\"";
//		strOrderInfo += "&";
//		strOrderInfo += "notify_url=" + "\""
//				+ "http://notify.java.jpxx.org/index.jsp" + "\"";
		
		return strOrderInfo;
	}
	
	/**
	 * get the out_trade_no for an order. 获取外部订单号
	 * 
	 * @return
	 */
	String getOutTradeNo() {
		SimpleDateFormat format = new SimpleDateFormat("MMddHHmmss");
		Date date = new Date();
		String strKey = format.format(date);

		java.util.Random r = new java.util.Random();
		strKey = strKey + r.nextInt();
		strKey = strKey.substring(0, 15);
		return strKey;
	}
	
	/**
	 * sign the order info. 对订单信息进行签名
	 */
	String sign(String signType, String content) {
		return Rsa.sign(content, this.m_private);
	}
	
	String getSignType() {
		String getSignType = "sign_type=" + "\"" + "RSA" + "\"";
		return getSignType;
	}
	/**
	 * get the char set we use. 获取字符集
	 */
	String getCharset() {
		String charset = "charset=" + "\"" + "utf-8" + "\"";
		return charset;
	}
	/**
	 * check some info.the partner,seller etc. 检测配置信息
	 */
	private boolean checkInfo() {
		String partner = this.m_parent;
		String seller = this.m_seller;
		if (partner == null || partner.length() <= 0 || seller == null
				|| seller.length() <= 0)
			return false;

		return true;
	}
	// 这里接收支付结果，支付宝手机端同步通知
		private Handler mHandler = new Handler() {
			public void handleMessage(Message msg) {
				try {
					String strRet = (String) msg.obj;

					Log.e(TAG, strRet);	// strRet范例：resultStatus={9000};memo={};result={partner="2088201564809153"&seller="2088201564809153"&out_trade_no="050917083121576"&subject="123456"&body="2010新款NIKE 耐克902第三代板鞋 耐克男女鞋 386201 白红"&total_fee="0.01"&notify_url="http://notify.java.jpxx.org/index.jsp"&success="true"&sign_type="RSA"&sign="d9pdkfy75G997NiPS1yZoYNCmtRbdOP0usZIMmKCCMVqbSG1P44ohvqMYRztrB6ErgEecIiPj9UldV5nSy9CrBVjV54rBGoT6VSUF/ufjJeCSuL510JwaRpHtRPeURS1LXnSrbwtdkDOktXubQKnIMg2W0PreT1mRXDSaeEECzc="}
					switch (msg.what) {
					case AlixId.RQF_PAY: {
						//
						closeProgress();

						BaseHelper.log(TAG, strRet);

						// 处理交易结果
						try {
							// 获取交易状态码，具体状态代码请参看文档
							String tradeStatus = "resultStatus={";
							int imemoStart = strRet.indexOf("resultStatus=");
							imemoStart += tradeStatus.length();
							int imemoEnd = strRet.indexOf("};memo=");
							tradeStatus = strRet.substring(imemoStart, imemoEnd);
							
							//先验签通知
							ResultChecker resultChecker = new ResultChecker(strRet);
							int retVal = resultChecker.checkSign();
							// 验签失败
							if (retVal == ResultChecker.RESULT_CHECK_SIGN_FAILED) {
								BaseHelper.showDialog(
										Test.this,
										"提示",
										getResources().getString(
												R.string.check_sign_failed),
										android.R.drawable.ic_dialog_alert);
							} else {// 验签成功。验签成功后再判断交易状态码
								if(tradeStatus.equals("9000"))//判断交易状态码，只有9000表示交易成功
									BaseHelper.showDialog(Test.this, "提示","支付成功。交易状态码："+tradeStatus, R.drawable.infoicon);
								else
								BaseHelper.showDialog(Test.this, "提示", "支付失败。交易状态码:"
										+ tradeStatus, R.drawable.infoicon);
							}

						} catch (Exception e) {
							e.printStackTrace();
							BaseHelper.showDialog(Test.this, "提示", strRet,
									R.drawable.infoicon);
						}
					}
						break;
					}

					super.handleMessage(msg);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		};

		//
		//
		/**
		 * the OnCancelListener for lephone platform. lephone系统使用到的取消dialog监听
		 */
		static class AlixOnCancelListener implements
				DialogInterface.OnCancelListener {
			Activity mcontext;

			AlixOnCancelListener(Activity context) {
				mcontext = context;
			}

			public void onCancel(DialogInterface dialog) {
				mcontext.onKeyDown(KeyEvent.KEYCODE_BACK, null);
			}
		}

		//
		// close the progress bar
		// 关闭进度框
		void closeProgress() {
			try {
				if (mProgress != null) {
					mProgress.dismiss();
					mProgress = null;
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		/**
		 * 返回键监听事件
		 */
		public boolean onKeyDown(int keyCode, KeyEvent event) {
			if (keyCode == KeyEvent.KEYCODE_BACK) {
				BaseHelper.log(TAG, "onKeyDown back");

				this.finish();
				return true;
			}

			return false;
		}

		//
		@Override
		public void onDestroy() {
			super.onDestroy();
			Log.v(TAG, "onDestroy");

			try {
				mProgress.dismiss();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	
}
