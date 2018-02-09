package com.estgp.bot.georeferencedwikipediamap;

import com.estgp.bot.georeferencedwikipediamap.weather_services.WeatherHttpClient;

import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class WeatherActivity extends FragmentActivity {
    /**
     * Aqui é definido o comportamento da WeatherActivity
     * onde se mostram os dados obtidos através do OpenWeatherMap
     * para o estado meteorológico da localização atual
     * É possível consultar, cidade, estado do tempo, temperatura atual, máxima e mínima
     * descrição, hora do nascer e pôr do sol
     *
     * weatherdata Instância da classe Weather, onde são feitos os GETs e SETs dos dados
     * weatherconect Instância da classe WeatherHttpClient, onde é tratado o request à API do OpenWeatherMap
     * timesunset TextView, placeholder para a hora do nascer do sol
     * timesunrise TextView, placeholder para a hora do pôr do sol
     * nowtemp TextView, placeholder para a temperatura atual
     * maxtemp TextView, placeholder para a temperatura máxima
     * mintemp TextView, placeholder para a temperatura mínima
     * desc TextView, placeholder para a descrição do estado do tempo
     * city TextView, placeholder para o nome da cidade atual
     * weatherIcon ImageView, placeholder para o ícone do estado do tempo atual
     * sunSetIcon ImageView, placeholder para o ícone do pôr do sol
     * sunRiseIcon ImageView, placeholder para o ícone do nascer do sol
     */
    private Weather weatherdata = null;
    private WeatherHttpClient weatherconect = null;

    private TextView timesunset;
    private TextView timesunrise;
    private TextView nowtemp;
    private TextView maxtemp;
    private TextView mintemp;
    private TextView desc;
    private TextView city;

    private ImageView weatherIcon;
    private ImageView sunSetIcon;
    private ImageView sunRiseIcon;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        /**
         * Método chamado para a execução da atividade WeatherActivity
         * e desenho do layout, após confirmar a existência de uma ligação
         * chama o método getLocation()
         */
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weather);
        isNetworkAvailable();
        getLocation();
    }


    private void getLocation() {
        /**
         * Método getLocation()
         * Onde é interpretado o Intent com a última localização obtido
         * na MapsActivity, são associadas as variáveis aos TextViews e ImageViews
         * e, havendo uma conexão à rede, são atribuídos os valores
         * aos objetos a mostrar no layout activity_maps
         */
        Intent intent = getIntent();
        String lat = intent.getStringExtra("last_lat");
        String lon = intent.getStringExtra("last_lon");

        timesunrise = findViewById(R.id.TimeSunRise);
        timesunset = findViewById(R.id.TimeSunSet);
        nowtemp = findViewById(R.id.Temp);
        maxtemp = findViewById(R.id.MaxTemp);
        mintemp = findViewById(R.id.MinTemp);
        desc = findViewById(R.id.Description);
        city = findViewById(R.id.City);

        weatherIcon = findViewById(R.id.Weather);
        sunSetIcon = findViewById(R.id.SunSet);
        sunRiseIcon = findViewById(R.id.SunRise);

        weatherconect = new WeatherHttpClient();
        weatherdata = new Weather();

        weatherdata = weatherconect.getWeatherData(lat, lon);
        if (isNetworkAvailable() == true) {
            city.setText(weatherdata.getCity());
            nowtemp.setText(weatherdata.temperature.getTemp());
            maxtemp.setText(weatherdata.temperature.getMaxTemp());
            mintemp.setText(weatherdata.temperature.getMinTemp());
            desc.setText(weatherdata.currentCondition.getDescr());
            timesunrise.setText(weatherdata.sys.getSunrise());
            timesunset.setText(weatherdata.sys.getSunset());
            weatherImage(weatherdata.currentCondition.getIcon());
            sunRiseIcon.setImageResource(R.drawable.sunrise);
            sunSetIcon.setImageResource(R.drawable.sunset);
        } else {
            city.setText("[ERROR] Unable to get weather data");
        }

    }

    public void sendMessage(View view) {
        /**
         * Associado ao evento OnClick do botão 'MAP'
         * transefere a execução para a atividade MapsActivity
         */
        Intent intent = new Intent(WeatherActivity.this, MapsActivity.class);
        startActivity(intent);
    }

    private boolean isNetworkAvailable() {
        /**
         * Procura uma ligação à Internet
         * @return activeNetworkInfo != null && activeNetworkInfo.isConnected() A interseção entre os
         * booleans activeNetworkInfo e activeNetworkInfo.isConnected() para determinação do estado da ligação
         */
        ConnectivityManager connectivityManager
                = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }

    private void weatherImage(String code) {
        /**
         * Switch case para selecionar o ícone a mostrar relativo
         * ao estado do tempo
         */
        switch (code) {
            case "01d":
                weatherIcon.setImageResource(R.drawable.icon_01d);
                break;
            case "02d":
                weatherIcon.setImageResource(R.drawable.icon_02d);
                break;
            case "03d":
                weatherIcon.setImageResource(R.drawable.icon_03d);
                break;
            case "04d":
                weatherIcon.setImageResource(R.drawable.icon_04d);
                break;
            case "09d":
                weatherIcon.setImageResource(R.drawable.icon_09d);
                break;
            case "10d":
                weatherIcon.setImageResource(R.drawable.icon_10d);
                break;
            case "11d":
                weatherIcon.setImageResource(R.drawable.icon_11d);
                break;
            case "13d":
                weatherIcon.setImageResource(R.drawable.icon_13d);
                break;
            case "50d":
                weatherIcon.setImageResource(R.drawable.icon_50d);
                break;
            case "01n":
                weatherIcon.setImageResource(R.drawable.icon_01n);
                break;
            case "02n":
                weatherIcon.setImageResource(R.drawable.icon_02n);
                break;
            case "03n":
                weatherIcon.setImageResource(R.drawable.icon_03n);
                break;
            case "04n":
                weatherIcon.setImageResource(R.drawable.icon_04n);
                break;
            case "09n":
                weatherIcon.setImageResource(R.drawable.icon_09n);
                break;
            case "10n":
                weatherIcon.setImageResource(R.drawable.icon_10n);
                break;
            case "11n":
                weatherIcon.setImageResource(R.drawable.icon_11n);
                break;
            case "13n":
                weatherIcon.setImageResource(R.drawable.icon_13n);
                break;
            case "50n":
                weatherIcon.setImageResource(R.drawable.icon_50n);
                break;
            default:
                weatherIcon.setImageResource(R.drawable.icon_01d);
                break;
        }
    }
}


