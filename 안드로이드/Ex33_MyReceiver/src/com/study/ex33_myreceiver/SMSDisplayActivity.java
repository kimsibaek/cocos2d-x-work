package com.study.ex33_myreceiver;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;

public class SMSDisplayActivity extends Activity {
	
	EditText editText1;
	EditText editText2;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView (R.layout.sms_display_activity);
		
		editText1 = (EditText)findViewById(R.id.editText1);
		editText2 = (EditText)findViewById(R.id.editText2);
		
		Intent intent = getIntent();
		displayMessage(intent);
		
	}
	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		displayMessage(intent);
		super.onNewIntent(intent);
		
	}
	
	private void displayMessage(Intent intent){
		String sender = intent.getStringExtra("sender");
		String contents = intent.getStringExtra("contents");
		
		editText1.setText(sender);
		editText2.setText(contents);
	}
}
