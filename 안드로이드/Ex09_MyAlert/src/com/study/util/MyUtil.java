package com.study.util;

import android.app.AlertDialog;
import android.content.Context;
import android.view.Gravity;
import android.widget.TextView;

public class MyUtil {
	public static void AlertShow(Context context, String msg) {
		AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setCancelable(false);
        builder.setMessage("\n"+msg+"\n");
        builder.setPositiveButton("확인", null);

        AlertDialog alert = builder.create();
        alert.show();

		// AlertDialog �쓽  媛��슫�뜲 �젙�젹�쓣 �쐞�븳.. setting
		// Must call show() prior to fetching text view 
		TextView messageView = (TextView)alert.findViewById(android.R.id.message);
		messageView.setGravity(Gravity.CENTER);
    }		

	public static void AlertShow(Context context, String msg, String title) {

		AlertDialog.Builder builder = new AlertDialog.Builder(context);
		builder.setIcon(android.R.drawable.ic_dialog_alert);
		builder.setTitle(title);
		builder.setCancelable(false);
		builder.setMessage("\n"+msg+"\n");
		builder.setPositiveButton("확인", null);

        AlertDialog alert = builder.create();
        alert.show();

        // AlertDialog �쓽  媛��슫�뜲 �젙�젹�쓣 �쐞�븳.. setting
		// Must call show() prior to fetching text view 
		TextView messageView = (TextView)alert.findViewById(android.R.id.message);
		messageView.setGravity(Gravity.CENTER);
    }		

}
