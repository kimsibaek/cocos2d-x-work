package com.study.ex02_lifecycle;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class NewActivity extends Activity{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.new_activity);
		
		// 인텐트에 전달된 데이타 구하기
				Intent intent = getIntent();
				final String sName = intent.getStringExtra("CustomerName");
						
				// 인텐트 종료하기
				Button button1 = (Button)findViewById(R.id.button1);
				button1.setOnClickListener(new OnClickListener() {
							
					@Override
					public void onClick(View v)
					{
						// 현재 인텐트 종료시 인텐트에 전달할 데이터 세팅 
						Intent intent = new Intent();
						intent.putExtra("BackData", "강감찬");
						setResult(10, intent);
						
						finish();
					}
				});
	}

	protected void onStart(){
		Toast.makeText(getApplicationContext(),  "onStart() 호출됨", Toast.LENGTH_SHORT).show();
		
		super.onStart();
	}
	
	protected void onResume(){
		Toast.makeText(getApplicationContext(),  "onResume() 호출됨", Toast.LENGTH_SHORT).show();
		
		super.onResume();
	}
	
	protected void onPause(){
		Toast.makeText(getApplicationContext(),  "onPause() 호출됨", Toast.LENGTH_SHORT).show();
		
		super.onPause();
	}
	
	protected void onStop(){
		Toast.makeText(getApplicationContext(),  "onStop() 호출됨", Toast.LENGTH_SHORT).show();
		
		super.onStop();
	}
	
	protected void onDestroy(){
		Toast.makeText(getApplicationContext(),  "onDestroy() 호출됨", Toast.LENGTH_SHORT).show();
		
		super.onDestroy();
	}
}
