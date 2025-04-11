package pt.estgp.es.spring.controllers;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.NonNull;
import org.springframework.web.filter.OncePerRequestFilter;

import java.io.IOException;

public class SpaWebFilter extends OncePerRequestFilter {
    //This class is used to forward internal requests to the SPA
    // instead of trying to find a matching controller in the backend
    // as a convention, /api/* requests are the only** ones handled in the backend
    // Only needed if running on the same port i.e. 8080
    @Override
    protected void doFilterInternal(@NonNull HttpServletRequest request, @NonNull HttpServletResponse response, @NonNull FilterChain filterChain) throws ServletException, IOException {
        String path = request.getRequestURI();

        if (shouldForwardToRoot(path)) {
            request.getRequestDispatcher("/").forward(request, response);
        } else {
            // Pass to the next filter or the application
            filterChain.doFilter(request, response);
        }
    }

    private boolean shouldForwardToRoot(String path) {
        return !path.startsWith("/api") && !path.contains(".") && path.matches("/(.*)");
    }
}
