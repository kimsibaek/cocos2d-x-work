package com.study.ex18_mylist6;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.Toast;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_activity);
		
		final SingerAdapter adapter = new SingerAdapter(this);
		
		SingerItem item1 = new SingerItem("È«±æµ¿", "010-1111-5678", R.drawable.face1);
		adapter.addItem(item1);
		SingerItem item2 = new SingerItem("ÀÌ¼ø½Å", "010-2222-9876", R.drawable.face2);
		adapter.addItem(item2);
		SingerItem item3 = new SingerItem("±èÀ¯½Å", "010-3333-7777", R.drawable.face3);
		adapter.addItem(item3);
		
		
		ListView listView1 = (ListView) findViewById(R.id.listView1);
		
		listView1.setAdapter(adapter);
		
		listView1.setOnItemClickListener(new OnItemClickListener(){
			
			public void onItemClick(AdapterView<?> arg0, View arg1, int position, long arg3){
				SingerItem item = (SingerItem) adapter.getItem(position);
				Toast.makeText(getApplicationContext(), "selected : " + item.getName(), Toast.LENGTH_SHORT).show();
			}
		});
			
	
	}

	
}
