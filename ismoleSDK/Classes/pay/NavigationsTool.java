package com.ismole.Navigations;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.util.Log;

public class NavigationsTool {

	public static String TOPATH = "/mnt/sdcard/.ismole/ldy/";
	private static Activity s_activity = null;
	private static WifiManager wifi;
	private static TelephonyManager telephony;

	public static void openURL(String url) {
		Intent intent = new Intent();
		Log.e("navigations", url);
		intent.setAction("android.intent.action.VIEW");
		Uri content_url = Uri.parse(url);
		intent.setData(content_url);
		Cocos2dxActivity.getContext().startActivity(intent);

	}

	public static int getStringCount(String str) {
		return str.length();
	}

	public static String getSubString(String str, int begin, int end) {
		return str.substring(begin, end);
	}

	public static String replaceString(String str, String src, String dist) {
		return str.replaceAll(src, dist);
	}

	public static void setActivity(Activity paramActivity) {
		s_activity = paramActivity;
		wifi = (WifiManager) s_activity.getSystemService(Context.WIFI_SERVICE);
		telephony = (TelephonyManager)s_activity.getSystemService(Context.TELEPHONY_SERVICE);
		if (!wifi.isWifiEnabled())
			wifi.setWifiEnabled(true);
	}

	public static String getMacAddress() {
		WifiInfo localWifiInfo = null;
		if ((wifi != null) && (s_activity != null)) {
			localWifiInfo = wifi.getConnectionInfo();
			if (localWifiInfo == null) {
				return "0";
			}
		}
		String str = localWifiInfo.getMacAddress();
		Log.v("Test", localWifiInfo.getMacAddress());
		return localWifiInfo.getMacAddress();
	}
	
	public static String getDeviceId(){
		if ((telephony != null) && (s_activity != null)) {
			return telephony.getDeviceId();
		}
		return "0";
	}

	public static int copyAssetToSdCardFile(String assetFileName,
			String toFile, Context pContext) {
		try {
			File workPath = new File(TOPATH);
			if (!workPath.exists()) {
				workPath.mkdirs();
				Log.v("Test", "mkdirs");
			} else {
				Log.v("Test", "not mkdirs");
			}
			Log.v("Test", assetFileName);
			InputStream fosfrom = pContext.getAssets().open(assetFileName);
			Log.v("Test", assetFileName);
			OutputStream fosto = new FileOutputStream(toFile);
			byte bt[] = new byte[1024];
			int c;
			while ((c = fosfrom.read(bt)) > 0) {
				fosto.write(bt, 0, c);
			}
			fosfrom.close();
			fosto.close();
			return 0;

		} catch (Exception ex) {
			return -1;
		}
	}

	/**
	 * 解压一个压缩文档 到指定位置
	 * 
	 * @param zipFileString
	 *            压缩包的名字
	 * @param outPathString
	 *            指定的路径
	 * @throws Exception
	 */
	public static void UnZipFolder(String zipFileString, String outPathString) {
		android.util.Log.v("XZip", "UnZipFolder(" + zipFileString + ", "
				+ outPathString + ")");
		try {
			java.util.zip.ZipInputStream inZip = new java.util.zip.ZipInputStream(
					new java.io.FileInputStream(zipFileString));
			java.util.zip.ZipEntry zipEntry;
			String szName = "";

			while ((zipEntry = inZip.getNextEntry()) != null) {
				szName = zipEntry.getName();

				if (zipEntry.isDirectory()) {

					// get the folder name of the widget
					szName = szName.substring(0, szName.length() - 1);
					java.io.File folder = new java.io.File(outPathString
							+ java.io.File.separator + szName);
					folder.mkdirs();

				} else {

					java.io.File file = new java.io.File(outPathString
							+ java.io.File.separator + szName);
					file.createNewFile();
					// get the output stream of the file
					java.io.FileOutputStream out = new java.io.FileOutputStream(
							file);
					int len;
					byte[] buffer = new byte[1024];
					// read (len) bytes into buffer
					while ((len = inZip.read(buffer)) != -1) {
						// write (len) byte from buffer at the position 0
						out.write(buffer, 0, len);
						out.flush();
					}
					out.close();
				}
			}// end of while

			inZip.close();
		} catch (Exception ex) {

		}
	}// end of func
}
