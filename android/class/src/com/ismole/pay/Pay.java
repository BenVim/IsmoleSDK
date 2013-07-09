/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.ismole.pay;
import org.cocos2dx.lib.Cocos2dxActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

public class Pay extends Cocos2dxActivity {
	public static Pay payObj;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		payObj = this;
	}
	static {
		System.loadLibrary("game");
	}
	
	public static void openWeb(String url) {
		Intent intent = new Intent();
		Log.e("navigations", url);
		intent.setAction("android.intent.action.VIEW");
		Uri content_url = Uri.parse(url);
		intent.setData(content_url);
		Cocos2dxActivity.getContext().startActivity(intent);
	}
	
	public static void openAlert(String title, String msg)
	{
		//Log.i("openAlert", "msg");
	        
//	        Dialog alertDialog = new AlertDialog.Builder(Pay.payObj). 
//	                setTitle("对话框的标题"). 
//	                setMessage("对话框的内容"). 
//	                setIcon(R.drawable.icon). 
//	                create(); 
//	        alertDialog.show(); 
	}
	
	public static void pay(String order, String product,String productDes,String appScheme, String parent,String seller,String notifyUrl,String alipayKey, int price)
	{
		//Pay.payObj->
		Log.e("Pay Log......", "pay");
		Intent intent = new Intent();
		intent.setClass(Pay.payObj, Test.class);
		intent.putExtra("order", order);
		intent.putExtra("product", product);
		intent.putExtra("productDes", productDes);
		intent.putExtra("appScheme", appScheme);
		intent.putExtra("parent", parent);
		intent.putExtra("seller", seller);
		intent.putExtra("notifyUrl", notifyUrl);
		intent.putExtra("alipayKey", alipayKey);
		intent.putExtra("price", price);
		Pay.payObj.startActivity(intent);
		Pay.payObj.overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left);
		//Pay.payObj.pay();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
	}
	
}
