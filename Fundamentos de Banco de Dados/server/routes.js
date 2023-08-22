const express = require('express');
const router = express.Router();
const Post = require('./Models/Post.js');
const MovieController = require('./Controllers/MovieController.js');
const ActorController = require('./Controllers/ActorController.js');
const DirectorController = require('./Controllers/DirectorController.js');

/* filmes */
router.get('/movie', MovieController.filterIdMovie);
router.get('/movies', MovieController.listarFilmes);
router.get('/movies/order/imdb', MovieController.moviesOrderIMDBR);
router.get('/movies/order/gross', MovieController.moviesOrderGross);
router.get('/movies/order/runtime', MovieController.moviesOrderRuntime);
router.get('/movies/order/year', MovieController.moviesOrderYear);
router.get('/movies/order/name', MovieController.moviesOrderName);
router.get('/movies/filter/name', MovieController.nameMovies);
router.get('/movies/filter/director', MovieController.directorMovies);
router.get('/movies/filter/year', MovieController.releasedYearMovies);
router.get('/movies/filter/rating', MovieController.ratingMovies);
router.get('/movies/actors', MovieController.atorMovies);
router.get('/movies/generos/filmes', MovieController.genreMovies);
router.get('/movies/genero', MovieController.FilmesGeneroDoAtor);
router.get('/charts/gender', MovieController.numberGenderEachMovies);

/* atores */
router.get('/actors', ActorController.listarAtores);
router.get('/actors/order/age', ActorController.actorsOrderAge);
router.get('/actors/order/name', ActorController.actorsOrderName);
router.get('/actors/order/height', ActorController.actorsOrderHeight);
router.get('/actors/filter/gender', ActorController.genderActor);
router.get('/actors/filter/country', ActorController.countryActor);
router.get('/actors/filter/name', ActorController.nameActor);
router.get('/actors/filter/height', ActorController.heightActors);
router.get('/actors/filter/ethnicity', ActorController.ethnicityActors);
router.get('/actors/maioresimdbr/actors', ActorController.moviesBiggersImbActors);
router.get('/actors/actors/colab', ActorController.actorCollaborationsWithDirectos);

/* diretores */
router.get('/directors', DirectorController.listarDiretores);
router.get('/directors/order/movies', DirectorController.orderDirectorMovies);
router.get('/directors/order/name', DirectorController.directorsOrderName);
router.get('/directors/filter/gender', DirectorController.genderDirector);
router.get('/directors/filter/name', DirectorController.nameDirector);
router.get('/directors/maioresimdbr/directors', DirectorController.moviesBiggersImdbrDirectors);

module.exports = router;
