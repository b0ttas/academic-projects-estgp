package com.estgp.bot.georeferencedwikipediamap.weather_services;

import android.os.StrictMode;

import com.estgp.bot.georeferencedwikipediamap.Weather;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class WeatherHttpClient {
    /**
     * Esta classe serve para fazer o pedido à API da OpenWeatherMap
     * e obter os dados retornados do pedido JSON
     *
     * BASE_URL URL base para a API
     * APPID APPID registado pata o uso da API
     * LANG Linguagem de retorno do pedido à API
     * METRIC Unidades a retornar do pedido à API
     * weather Instância da classe Weather, onde são guardados os dados metereológicos
     */

    private static String BASE_URL = "http://api.openweathermap.org/data/2.5/weather?";
    private static String APPID = "&appid=78382d8b7e37195dcacfcee83b2a3966";
    private static String LANG = "&lang=en";
    private static String METRIC = "&units=metric";
    private Weather weather = null;

    public Weather getWeatherData(String lat, String lon) {
        /**
         * Aqui é executado o pedido à API da OpenWeatherMap
         * através dos argumentos 'lat' e 'lon' são devolvidos os
         * dados metereológicos existentes na localização atual, este método
         * faz o pedido e envia o resultado para a classe JSONWeatherParcer
         * onde a resposta é processada
         *
         * @param parser JSONGeoNamesParser, onde se vai guardar o JSONObject json com o conteúdo da resposta
         * @param con  HttpURLConnection, serve para establecer a ligação
         * @param is InputStream, usado para ler  a resposta
         * @param coords String com os argumentos 'lat' e 'lon'
         *
         * @return poi, classe GeoNames com os dados lidos
         */

        JSONWeatherParser parser;
        HttpURLConnection con = null;
        InputStream is = null;
        String coords = "lat=" + lat + "&lon=" + lon;

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        try {
            String urlString = BASE_URL + coords + APPID + LANG + METRIC;
            URL url = new URL(urlString);
            con = (HttpURLConnection) url.openConnection();
            con.setReadTimeout(100000);
            con.setConnectTimeout(100000);
            con.setRequestMethod("GET");
            con.setDoInput(true);
            con.connect();

            StringBuffer buffer = new StringBuffer();
            is = con.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String line = null;
            while ((line = br.readLine()) != null)
                buffer.append(line + "\r\n");
            is.close();
            JSONObject json = new JSONObject(buffer.toString());
            parser = new JSONWeatherParser();
            weather = new Weather();
            weather = parser.parse(json);
            con.disconnect();

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
            } catch (Throwable t) {
            }
            try {
                con.disconnect();
            } catch (Throwable t) {
            }
        }
        return weather;
    }
}