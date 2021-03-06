package com.ismole.pay;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageButton;

public class QimiFullSceneWeb extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_qimi_full_scene_web);
		
		Intent i = getIntent(); 
		String imageUrls = i.getStringExtra("url");  
        
        WebView mWebView=(WebView) findViewById(R.id.wv1);
        WebSettings webSettings = mWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setSupportZoom(true);
        mWebView.requestFocus();
        mWebView.loadUrl(imageUrls);
        WebViewClient client = new WebViewClient() { 
        @Override
        
        public void onPageStarted(WebView view, String url, Bitmap favicon) {  
        	super.onPageStarted(view, url, favicon);
        	}
        };
         
        mWebView.setWebViewClient(client);
        
        
        ImageButton btn = (ImageButton)findViewById(R.id.backBtn);
        btn.setOnClickListener(new OnClickListener()
		{
          public void onClick(View v)
          {
        	  QimiFullSceneWeb.this.finish();
          }
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_qimi_full_scene_web, menu);
		return true;
	}

}
