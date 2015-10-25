package com.example.marcin.joker;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

// linux:[cmd]
// windows:[cmd]
// linux_fb_post:[tresc postu]
// windows_fb_post:[tresc postu]
// matrix

public class MainActivity extends AppCompatActivity {
    private final static int REQUEST_ENABLE_BT = 1;
    private final static String JokerName = "NOTHING";
    private BluetoothDevice mmDevice = null;
    private BluetoothAdapter mBluetoothAdapter;
    private OutputStream mmOutputStream;
    private InputStream mmInputStream;
    private BluetoothSocket mmSocket;
    private boolean connected = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button buttonWindowsHack = (Button) findViewById(R.id.winFirefox);
        buttonWindowsHack.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if (!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    String msg = "ccpccoqcwindows_steal_ff+";
                    msg += "\n";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        final Button buttonLinuxHack = (Button) findViewById(R.id.linFirefox);
        buttonLinuxHack.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if (!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    String msg = "ccpccoqclinux_steal_ff+";
                    msg += "\n";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        final Button buttonLinuxFacebook = (Button) findViewById(R.id.linFb);
        buttonLinuxFacebook.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if(!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    TextView editBox = (TextView) findViewById(R.id.editText);
                    String msg = "ccpccoqclinux_fb_post:";
                    msg += editBox.getText().toString();
                    msg += "+";
                    msg += "\n";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        final Button buttonWindowsFacebook = (Button) findViewById(R.id.winFb);
        buttonWindowsFacebook.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if(!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    TextView editBox = (TextView) findViewById(R.id.editText);
                    String msg = "ccpccoqcwindows_fb_post:";
                    msg += editBox.getText().toString();
                    msg += "+";
                    msg += "\n";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        final Button buttonLinuxCommand = (Button) findViewById(R.id.linCmd);
        buttonLinuxCommand.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if(!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    TextView editBox = (TextView) findViewById(R.id.editText);
                    String msg = "ccpccoqclinux:";
                    msg += editBox.getText().toString();
                    msg += "+";
                    msg += "\n";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        final Button buttonLinuxMatrix = (Button) findViewById(R.id.matrix);
        buttonLinuxMatrix.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                if(!connected || !mBluetoothAdapter.isEnabled()) {
                    Toast.makeText(getApplicationContext(), "You must turn on Bluetooth", Toast.LENGTH_LONG).show();
                } else {
                    TextView editBox = (TextView) findViewById(R.id.editText);
                    String msg = "ccpccoqcmatrix+";
                    try {
                        mmOutputStream.write(msg.getBytes());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        setJoker();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if (requestCode == REQUEST_ENABLE_BT) {
            if(resultCode == RESULT_OK) {
                progressBluetooth();
            }
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private void progressBluetooth()
    {
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if(pairedDevices.size() > 0)
        {
            for(BluetoothDevice device : pairedDevices)
            {
                if(device.getName().equals(JokerName))
                {
                    mmDevice = device;
                    break;
                }
            }
        }

        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
        try {
            mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            mmSocket.connect();
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            mmOutputStream = mmSocket.getOutputStream();
            mmInputStream = mmSocket.getInputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }

        connected = true;
        TextView jokerInfo = (TextView)findViewById(R.id.jokerInfo);
        jokerInfo.setText("Joker found!");
    }

    private void setJoker()
    {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(mBluetoothAdapter == null)
        {
            System.out.println("Bluetooth not working :(");
        }
        if(!mBluetoothAdapter.isEnabled())  {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        } else
        {
            progressBluetooth();
        }
    }
}
