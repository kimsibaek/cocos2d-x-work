package com.study.ex09_myalert;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

import com.study.util.CustomProgressDialog;
import com.study.util.MyUtil;

public class MainActivity extends Activity {

	public static CustomProgressDialog progressDialog = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				MyUtil.AlertShow(MainActivity.this, "아이디를 입력해 주세요", "알림");
			}
		});
		Button button2 = (Button)findViewById(R.id.button2);
		button2.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				MyUtil.AlertShow(MainActivity.this, "아이디를 입력해 주세요");
			}
		});
		Button button3 = (Button)findViewById(R.id.button3);
		button3.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
				
				builder.setMessage("앱을 종료하시겠습니까?")
						.setIcon(android.R.drawable.ic_dialog_alert)
						.setTitle("알림")
						.setCancelable(false)
						.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface dialog, int id) {
								// TODO Auto-generated method stub
								Toast.makeText(getApplicationContext(), "ID value is " + Integer.toString(id), Toast.LENGTH_SHORT).show();
								dialog.cancel();
							}
						})
						.setNegativeButton("No", new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface dialog, int id) {
								// TODO Auto-generated method stub
								Toast.makeText(getApplicationContext(), "ID value is " + Integer.toString(id), Toast.LENGTH_SHORT).show();
								dialog.cancel();
							}
						});
				AlertDialog alert = builder.create();
				alert.show();
			}
		});
		Button button4 = (Button)findViewById(R.id.button4);
		button4.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				if(progressDialog == null || !progressDialog.isShowing()){
					progressDialog = CustomProgressDialog.show(MainActivity.this, "", "처리중입니다", true, true, null);
				}
			}
		});
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event){
		return super.onKeyDown(keyCode, event);
	}
}
