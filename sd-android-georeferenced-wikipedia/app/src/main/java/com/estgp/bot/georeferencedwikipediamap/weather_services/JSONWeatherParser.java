package com.estgp.bot.georeferencedwikipediamap.weather_services;

import com.estgp.bot.georeferencedwikipediamap.Weather;

import org.json.JSONArray;
import org.json.JSONObject;

public class JSONWeatherParser {
    /**
     * Classe encarregue de interpretar e selecionar os dados provenientes da resposta
     * guardada no JSONObject json
     *
     * weather Instância da classe Weather para onde os dados obtidos são enviados
     */
    private Weather weather = null;

    public Weather parse(JSONObject json) {
        /**
         * Aqui procede-se ao tratamento dos dados provenientes da OpenWeatherMap
         * a resposta é dividida segundo os seus elementos num JSONArray para
         * a desccrição do estado do tempo e o ícone a ele referente
         * e dois JSONObjects para as horas do nascer/pôr do sol e as
         * temperaturas atual, mínima e máxima
         *
         * @param weather Instância da classe GeoNames para o envio dos dados processados
         * @return weather Retorno da classe weather com os dados
         */
        weather = new Weather();
        try {
            weather.setCity(json.getString("name"));
            JSONArray array_weather = json.getJSONArray("weather");
            JSONObject json_sys = json.getJSONObject("sys");
            JSONObject json_main = json.getJSONObject("main");

            int count_weather = array_weather.length();

            for (int i = 0; i < count_weather; i++) {
                weather.currentCondition.setDescr(array_weather.getJSONObject(i).getString("description"));
                weather.currentCondition.setIcon(array_weather.getJSONObject(i).getString("icon"));
            }

            weather.temperature.setMaxTemp(json_main.getDouble("temp_max"));
            weather.temperature.setMinTemp(json_main.getDouble("temp_min"));
            weather.temperature.setTemp(json_main.getDouble("temp"));

            weather.sys.setSunrise(json_sys.getString("sunrise"));
            weather.sys.setSunset(json_sys.getString("sunset"));

            return weather;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return weather;
    }
}