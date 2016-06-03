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
		
		// ����Ʈ�� ���޵� ����Ÿ ���ϱ�
				Intent intent = getIntent();
				final String sName = intent.getStringExtra("CustomerName");
						
				// ����Ʈ �����ϱ�
				Button button1 = (Button)findViewById(R.id.button1);
				button1.setOnClickListener(new OnClickListener() {
							
					@Override
					public void onClick(View v)
					{
						// ���� ����Ʈ ����� ����Ʈ�� ������ ������ ���� 
						Intent intent = new Intent();
						intent.putExtra("BackData", "������");
						setResult(10, intent);
						
						finish();
					}
				});
	}

	protected void onStart(){
		Toast.makeText(getApplicationContext(),  "onStart() ȣ���", Toast.LENGTH_SHORT).show();
		
		super.onStart();
	}
	
	protected void onResume(){
		Toast.makeText(getApplicationContext(),  "onResume() ȣ���", Toast.LENGTH_SHORT).show();
		
		super.onResume();
	}
	
	protected void onPause(){
		Toast.makeText(getApplicationContext(),  "onPause() ȣ���", Toast.LENGTH_SHORT).show();
		
		super.onPause();
	}
	
	protected void onStop(){
		Toast.makeText(getApplicationContext(),  "onStop() ȣ���", Toast.LENGTH_SHORT).show();
		
		super.onStop();
	}
	
	protected void onDestroy(){
		Toast.makeText(getApplicationContext(),  "onDestroy() ȣ���", Toast.LENGTH_SHORT).show();
		
		super.onDestroy();
	}
}
