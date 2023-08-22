const Sequelize = require('sequelize')


const sequelize = new Sequelize('movies', 'root', 'Eunao!!Gostode4', {
  host: '127.0.0.1',
  dialect: 'mysql',
  port: 3306
})

module.exports = {
  Sequelize: Sequelize,
  sequelize: sequelize
}

sequelize
  .authenticate()
  .then(() => {
    console.log('Conexão com o banco de dados estabelecida com sucesso.');
  })
  .catch((error) => {
    console.error('Erro ao conectar-se ao banco de dados:', error);
  });