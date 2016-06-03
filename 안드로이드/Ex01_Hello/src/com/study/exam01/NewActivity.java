package com.study.exam01;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class NewActivity extends Activity {

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
		
		// �佺Ʈ�� ���޵� ������ �����ֱ� 
		Button button2 = (Button)findViewById(R.id.button2);
		button2.setOnClickListener(new OnClickListener() {
					
			@Override
			public void onClick(View v)
			{
				Toast.makeText(getApplicationContext(), "CustomerName : " + sName, Toast.LENGTH_SHORT).show();
			}
		});
		
	}

}
