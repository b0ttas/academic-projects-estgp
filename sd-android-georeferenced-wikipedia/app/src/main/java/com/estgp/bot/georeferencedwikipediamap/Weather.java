package com.estgp.bot.georeferencedwikipediamap;

import java.util.Date;

public class Weather {
    /**
     * Classe Weather, onde são definidos getters e setters
     * para o tratamento dos dados meteorológicos obtidos via OpenWeatherMap
     *
     * city String, onde é guardada a cidade atual
     * sys Classe onde estão os setters e getters para 'sunset' e 'sunrise'
     * currentCondition Classe onde estão os setters e getters para 'descr' e 'icon'
     * temperature Classe onde estão os setters e getters para 'temp', 'minTemp' e 'maxTemp'
     */

    private String city;
    public Sys sys = new Sys();
    public CurrentCondition currentCondition = new CurrentCondition();
    public Temperature temperature = new Temperature();


    public class Sys {
        /**
         * Classe Sys, onde se definem e retornam as horas para os eventos 'sunrise' e 'sunset'
         * @return String, 'sunrise' e 'sunset' que contêm as horas para os eventos do mesmo nome
         */
        public String getSunset() {

            String epochString = sunset;
            long epoch = Long.parseLong(epochString);
            Date expiry = new Date(epoch * 1000);
            Integer Hours = expiry.getHours();
            Integer Min = expiry.getMinutes();
            String zero_hours = "", zero_min = "";
            if (Hours < 10) {
                zero_hours = "0";
            }
            if (Min < 10) {
                zero_min = "0";
            }

            String ret = zero_hours + Hours.toString() + "h:" + zero_min + Min.toString() + "m";
            return ret;
        }

        public void setSunset(String sunset) {

            this.sunset = sunset;
        }

        public String getSunrise() {
            String epochString = sunrise;
            long epoch = Long.parseLong(epochString);
            Date expiry = new Date(epoch * 1000);
            Integer Hours = expiry.getHours();
            Integer Min = expiry.getMinutes();
            String zero_hours = "", zero_min = "";
            if (Hours < 10) {
                zero_hours = "0";
            }
            if (Min < 10) {
                zero_min = "0";
            }

            String ret = zero_hours + Hours.toString() + "h:" + zero_min + Min.toString() + "m";
            return ret;
        }

        public void setSunrise(String sunrise) {
            this.sunrise = sunrise;
        }

        public String sunset;
        public String sunrise;

    }

    public class CurrentCondition {
        /**
         * Classe CurrentCondition, onde se definem e retornam a descrição
         * e o ícone correspondente ao estado do tempo
         *
         * String, 'descr' e 'icon' contêm os dados de estado do tempo e o nome do ícone a apresentar
         */
        private String descr;
        private String icon;

        public String getDescr() {
            return descr;
        }

        public void setDescr(String descr) {
            this.descr = descr;
        }

        public String getIcon() {
            return icon;
        }

        public void setIcon(String icon) {
            this.icon = icon;
        }

    }

    public class Temperature {
        /**
         * Classe Temperature, onde se definem e retornam as temperaturas, atual, mínima e máxima
         *
         * Double, 'temp' 'minTemp' 'maxTemp', que contêm as temperaturas
         */

        public double temp;
        public double minTemp;
        public double maxTemp;

        public String getTemp() {
            String t = Double.toString(temp);
            return t + "º";
        }

        public void setTemp(double temp) {
            this.temp = temp;
        }

        public String getMinTemp() {
            String t = Double.toString(minTemp);
            return t + "º";
        }

        public void setMinTemp(double minTemp) {
            this.minTemp = minTemp;
        }

        public String getMaxTemp() {
            String t = Double.toString(maxTemp);
            return t + "º";
        }

        public void setMaxTemp(double maxTemp) {
            this.maxTemp = maxTemp;
        }
    }

    public String getCity() {
        /**
         * Método getCity()
         * Retorna uma String com o nome da cidade atual
         */
        return city;
    }

    public void setCity(String city) {
        /**
         * Método setCity()
         * Define uma String com o nome da cidade atual
         */
        this.city = city;
    }
}