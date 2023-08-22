var DataTypes = require("sequelize").DataTypes;
var _actor = require("./actor");
var _cast = require("./cast");
var _director = require("./director");
var _movie = require("./movie");

function initModels(sequelize) {
  var actor = _actor(sequelize, DataTypes);
  var cast = _cast(sequelize, DataTypes);
  var director = _director(sequelize, DataTypes);
  var movie = _movie(sequelize, DataTypes);

  cast.belongsTo(actor, { as: "actor", foreignKey: "actorID"});
  actor.hasMany(cast, { as: "casts", foreignKey: "actorID"});
  movie.belongsTo(director, { as: "director", foreignKey: "directorId"});
  director.hasMany(movie, { as: "movies", foreignKey: "directorId"});
  cast.belongsTo(movie, { as: "movie", foreignKey: "movieId"});
  movie.hasMany(cast, { as: "casts", foreignKey: "movieId"});

  return {
    actor,
    cast,
    director,
    movie,
  };
}
module.exports = initModels;
module.exports.initModels = initModels;
module.exports.default = initModels;
