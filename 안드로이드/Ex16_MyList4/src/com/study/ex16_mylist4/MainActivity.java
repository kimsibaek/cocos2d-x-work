package com.study.ex16_mylist4;

import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
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
		
		//ArrayAdapter<String> adapter;
		//adapter = new ArrayAdapter<String> (this, android.R.layout.simple_list_item_1, names);
		
		
		
		final MyAdapter adapter = new MyAdapter();
		
		SingerItem item1 = new SingerItem("È«±æµ¿", "20", R.drawable.face1);
		adapter.addItem(item1);
		SingerItem item2 = new SingerItem("ÀÌ¼ø½Å", "25", R.drawable.face2);
		adapter.addItem(item2);
		SingerItem item3 = new SingerItem("±èÀ¯½Å", "30", R.drawable.face3);
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

	class MyAdapter extends BaseAdapter {
		
		ArrayList<SingerItem> items = new ArrayList<SingerItem>();
		
		public void addItem(SingerItem item){
			items.add(item);
		}
		
		public int getCount(){
			return items.size();
		}
		
		public Object getItem(int position){
			return items.get(position);
		}
		
		public long getItemId(int position){
			return position;
		}
		
		public View getView(int position, View convertView, ViewGroup parent){
			
			SingerItemView view = new SingerItemView(getApplicationContext());
			SingerItem item = items.get(position);
			view.setName(item.getName());
			view.setAge(item.getAge());
			view.setImage(item.getResId());
			
			return view;
		}
	}
	
}
