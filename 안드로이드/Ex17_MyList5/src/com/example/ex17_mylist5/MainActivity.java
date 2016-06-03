package com.example.ex17_mylist5;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity extends Activity {

	EditText editText1;
	EditText editText2;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		final SingerAdapter adapter = new SingerAdapter(this);
		
		SingerItem item1 = new SingerItem("ȫ�浿", "20", R.drawable.face1);
		adapter.addItem(item1);
		SingerItem item2 = new SingerItem("�̼���", "25", R.drawable.face2);
		adapter.addItem(item2);
		SingerItem item3 = new SingerItem("������", "30", R.drawable.face3);
		adapter.addItem(item3);
		
		
		ListView listView1 = (ListView) findViewById(R.id.listView1);
		
		listView1.setAdapter(adapter);
		
		listView1.setOnItemClickListener(new OnItemClickListener(){
			
			public void onItemClick(AdapterView<?> arg0, View arg1, int position, long arg3){
				SingerItem item = (SingerItem) adapter.getItem(position);
				Toast.makeText(getApplicationContext(), "selected : " + item.getName(), Toast.LENGTH_SHORT).show();
			}
		});
				
		editText1 = (EditText) findViewById(R.id.editText1);
		editText2 = (EditText) findViewById(R.id.editText2);
		
		Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v){
				String inputName = editText1.getText().toString();
				String inputAge = editText2.getText().toString();
				
				SingerItem item = new SingerItem(inputName, inputAge, R.drawable.face1);
				adapter.addItem(item);
				adapter.notifyDataSetChanged();
			}
		});
	}

}
